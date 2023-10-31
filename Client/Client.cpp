/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Client
*/

#include "Client.hpp"

RType::Client::Client(int ac, char **av) : 
_commands({
{(playerPing), &RType::Client::sendPing},
{illegalAction, &RType::Client::handleNonAuthorized},
{newPlayerConnected, &RType::Client::newPlayerToRoom},
{givePlayerId, &RType::Client::getNewId},
{moveAnEntity, &RType::Client::moveEntity},
{destroyedRoom, &RType::Client::quitRoom},
{serverStop, &RType::Client::serverStopped},
{entityType, &RType::Client::setEntityType},
{removeEntity, &RType::Client::removeAnEntity},
{valueSet, &RType::Client::setValues},
{nbOfEntities, &RType::Client::syncNbOfEntities},
{playerDeconnected, &RType::Client::quitRoom},
{message, &RType::Client::newMessage},
}),
_buttonList("../Assets/insanibu.ttf"),
_parallax(_texture),
_parallaxGnome(_texture),
_popUp("Welcome the the R-Type !", "../Assets/insanibu.ttf"),
_menu(this->_popUp, [this]{
    #ifdef __unix__
        int random = std::rand() % 1000 + 3000; 
        int pid = fork();
        if (!pid) {
            std::system(std::string("./r-type_server "+ std::to_string(random) + " ../test.cfg").c_str());
            std::exit(0);
        }
        this->_serverPid = pid;
        this->_serverIp = "127.0.0.1";
        this->_serverPort = random;
        return;
    #endif
    this->_popUp.setText("Feature only available in linux systems");
})
{
    std::srand(std::time(NULL));
    if (ac < 3)
        throw std::invalid_argument("Not enought arguments");
    this->_keysDown = {
            {Events::Up, false},
            {Events::Down, false},
            {Events::Left, false},
            {Events::Right, false},};
    this->_sendInputTime = std::chrono::steady_clock::now();
    this->_lifeBar = std::make_unique<LifeBar>();
    this->_actualScreen = Screens::menu;
    this->_gameAsStarted = false;
    this->_inputs = {};
    this->_mouseClicked = false;
    this->_serverIp = av[1];
    this->_serverPid = -1;
    this->_serverPort = std::stoi(av[2]);
    this->_mutex = std::make_unique<std::mutex>();
    // this->_buttonList.addButtons([this]{std::cout << "Hello world !" << std::endl;}, "../Assets/buttonTest.png", "Hello !", sf::Vector2f(10.0, 10.0), sf::IntRect(0, 0, 150, 100), 100, 0);
    this->_window = std::make_unique<sf::RenderWindow>(sf::VideoMode::getDesktopMode(), "R-Type" /*,sf::Style::Fullscreen */);
    // if (this->_music.openFromFile("../Assets/music.ogg") != -1)
        // this->_music.play();
    this->_socket = std::make_unique<Utils::SocketHandler>("127.0.0.1", 4001 + std::rand() % 3000, std::list<int>({keyPressed, entityType, playerPing, newPlayerConnected, givePlayerId, destroyedRoom, serverStop, entityType, removeEntity, playerDeconnected, newRoomIsCreated, playerGetId, givePlayerId}));
    this->_threadIsOpen = true;
    this->_actualId = -1;
    this->_predicate = std::make_unique<Prediction>(this->_entities, this->_predictionCore, this->_inputs);
    this->_infosThread = std::make_unique<std::thread>(&RType::Client::infosThread, this);
    this->run();
}

void RType::Client::updateInputs(void)
{
    std::unique_lock<std::mutex> lock(*this->_mutex);
    this->handleInputs();
    if (this->_keysDown[Events::Up])
        this->_inputs.push_back(Events::Up);
    if (this->_keysDown[Events::Left])
        this->_inputs.push_back(Events::Left);
    if (this->_keysDown[Events::Down])
        this->_inputs.push_back(Events::Down);
    if (this->_keysDown[Events::Right])
        this->_inputs.push_back(Events::Right);
}

void RType::Client::handleInputs(void)
{
    sf::Event event;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        this->_mouseClicked = true;
    else
        this->_mouseClicked = false;
    while (this->_window->pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case (sf::Keyboard::Up) :
                    this->_keysDown[Events::Up] = true;
                    break;
                case (sf::Keyboard::Down) :
                    this->_keysDown[Events::Down] = true;
                    break;
                case (sf::Keyboard::Left) :
                    this->_keysDown[Events::Left] = true;
                    break;
                case (sf::Keyboard::Right) :
                    this->_keysDown[Events::Right] = true;
                    break;
                case (sf::Keyboard::Escape) :
                    this->quitActualRoom();
                    break;
                case (sf::Keyboard::C) :
                    if (this->_msgPanel.isOpen())
                        this->_msgPanel.closePanel();
                    else
                        this->_msgPanel.openPanel();
                case (sf::Keyboard::Space) :
                    if (!this->shooting) {
                        this->shotTime = std::chrono::steady_clock::now();
                        this->shooting = true;
                    }
                    break;
                case (sf::Keyboard::W) :
                    sf::Texture text;
                    text.create(1920, 1080);
                    text.update(*this->_window);
                    auto img = text.copyToImage();
                    img.saveToFile("screenshoot.png");
                    break;

            }
        }
        if (event.type == sf::Event::KeyReleased) {
            switch (event.key.code) {
                case (sf::Keyboard::Up) :
                    this->_keysDown[Events::Up] = false;
                    break;
                case (sf::Keyboard::Down) :
                    this->_keysDown[Events::Down] = false;
                    break;
                case (sf::Keyboard::Left) :
                    this->_keysDown[Events::Left] = false;
                    break;
                case (sf::Keyboard::Right) :
                    this->_keysDown[Events::Right] = false;
                    break;
                case (sf::Keyboard::Escape) :
                    this->_inputs.push_back(Events::CloseWindow);
                    break;
                case (sf::Keyboard::Space) :
                    if (this->shooting) {
                        auto time = std::chrono::steady_clock::now();
                        if (std::chrono::duration_cast<std::chrono::milliseconds>(time - this->shotTime).count() >= 250)
                            this->_inputs.push_back(Events::PiercingShoot);
                        else
                            this->_inputs.push_back(Events::Shoot);
                        this->shooting = false;
                    }
                    break;
                case (sf::Mouse::Left || sf::Mouse::Right) :
                    this->_mouseClicked = false;
                    break;
            }
        }
    }
}

void RType::Client::run()
{
    while (_window->isOpen()) {
        switch (this->_actualScreen) {
        case game:
            this->gameLoop();
            break;
        case menu:
            this->displayMenu();
            break;
        }
    }
}

void RType::Client::infosThread()
{
    while (this->_threadIsOpen) {
        Utils::MessageParsed_s msg = this->_socket->receive();
        if (this->_actualScreen == menu) {
            this->_menu.addMessage(msg);
            continue;
        }
        auto it = this->_commands.find(msg.msgType);
        if (it == this->_commands.end())
            continue;
        (this->*it->second)(msg);
    }
}

void RType::Client::sendPing(const Utils::MessageParsed_s &recMsg)
{
    auto msg = this->buildEmptyMsg(playerPing);
    this->_socket->send(msg);
}


void RType::Client::handleNonAuthorized(const Utils::MessageParsed_s &msg)
{
    this->_popUp.setText("Unauthorized action with type :" + std::to_string(static_cast<int>(msg.bytes[2])));
    if (msg.bytes[2] == newRoomIsCreated) {
        this->_mutex->lock();
        this->_actualRoom = 0;
        this->_mutex->unlock();
        return this->joinRoom(1);
    }
}

RType::Utils::MessageParsed_s RType::Client::buildEmptyMsg(const ComCodes &code)
{
    Utils::MessageParsed_s msg;
    msg.msgType = code;
    msg.senderIp = this->_serverIp;
    msg.senderPort = this->_serverPort;
    return msg;
}

void RType::Client::joinRoom(unsigned char roomNb)
{
    Utils::MessageParsed_s msg = this->buildEmptyMsg(newPlayerConnected);
    msg.bytes[0] = roomNb;
    this->_socket->send(msg);
    std::unique_lock<std::mutex>(*this->_mutex);
    this->_actualRoom = 1;
}

void RType::Client::createRoom(unsigned char roomNb)
{
    Utils::MessageParsed_s msg = this->buildEmptyMsg(newRoomIsCreated);
    msg.bytes[0] = roomNb;
    this->_socket->send(msg);
    std::unique_lock<std::mutex> lock(*this->_mutex);
    this->_actualRoom = 1;
    this->_entities.addEntity(std::make_shared<Player>(Position(0, 0, 1080, 1920)), 0);
}

void RType::Client::newPlayerToRoom(const Utils::MessageParsed_s &msg)
{
    std::unique_lock<std::mutex> lock(*this->_mutex);
    this->_popUp.setText("New player to Room !");
    auto pl = std::make_shared<Player>(Position(0, 0, 1080, 1920));
    this->_lifeBar->setLifeBarToPlayer(pl);
    this->_entities.addEntity(pl, msg.getFirstShort());
}

void RType::Client::getNewId(const Utils::MessageParsed_s &msg)
{
    std::unique_lock<std::mutex> lock(*this->_mutex);
    this->_actualId = msg.getFirstShort();
}

bool RType::Client::checkAsId()
{
    if (this->_actualId != -1)
        return true;
    auto msg = this->buildEmptyMsg(playerGetId);
    this->_socket->send(msg);
    return false;
}

void RType::Client::moveEntity(const Utils::MessageParsed_s &msg)
{
    std::unique_lock<std::mutex> lock(*this->_mutex);
    // if (msg.getThirdShort() != 0)
    //     std::cout << "Get message from entity" << msg.getThirdShort() << std::endl;
    auto it = this->_entities._entities.find(msg.getThirdShort());
    if (it == this->_entities._entities.end()) {
        this->getEntityType(msg.getThirdShort());
        return;
    }
    if (it->second->getEntityType() != msg.bytes[6]) {
        lock.unlock();
        return this->changeTypeEntityAndMove(msg, it);
    }
    it->second->setPosition(Position(msg.getFirstShort(), msg.getSecondShort(), 1080, 1920));
}

void RType::Client::quitRoom(const Utils::MessageParsed_s &msg)
{
    std::unique_lock<std::mutex> lock(*this->_mutex);
    if (msg.msgType == playerDeconnected && (msg.bytes[1] != this->_actualId)) {
        this->_popUp.setText("Player " + std::to_string(static_cast<int>(msg.bytes[1])) + " has quitted the room.");
        return (void)this->_entities.removeEntity(msg.bytes[1]);
    }
    this->_popUp.setText("You have quitted/kicked from your Room");
    this->_actualId = -1;
    this->_quittedRoom = true;
    this->_actualScreen = menu;
    this->_entities._entities.clear();
    // this->_threadIsOpen = false;
    // this->_window->close();
    // exit(0);
}

void RType::Client::serverStopped(const Utils::MessageParsed_s &msg)
{
    (void)msg;
    this->_actualId = -1;
    this->_threadIsOpen = false;
    this->_window->close();
    exit(0);
}

void RType::Client::getEntityType(unsigned short entity)
{
    auto it = this->_getIdLimiters.find(entity);
    if (it == this->_getIdLimiters.end())
        this->_getIdLimiters.insert({entity, std::chrono::steady_clock::now()});
    else if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - it->second).count() < GET_ID_LIMIT_TIME)
        return;
    auto msg = this->buildEmptyMsg(entityType);
    msg.setFirstShort(entity);
    this->_socket->send(msg);
    if (it != this->_getIdLimiters.end())
        it->second = std::chrono::steady_clock::now();
}

void RType::Client::setEntityType(const Utils::MessageParsed_s &msg)
{
    switch (msg.getSecondShort()) {
        case RType::player:
            return this->newPlayerToRoom(msg);
        case RType::bydos:
            return this->newBydosToRoom(msg);
        case RType::bydosShoot:
            return this->newEnemyShoot(msg);
        case RType::tourre:
            return this->newTourreToRoom(msg);
        case RType::playerShoot :
            return this->newMyShoot(msg);
        case RType::percingShoot :
            return this->newPercingShoot(msg);
        case RType::coin :
            return this->newCoin(msg);
    }
}

void RType::Client::newCoin(const Utils::MessageParsed_s &msg)
{
    std::unique_lock<std::mutex> lock(*this->_mutex);
    auto it = this->_entities._entities.find(msg.getFirstShort());
    if (it != this->_entities._entities.end())
        return;
    this->_entities.addEntity(std::make_shared<Coin>(Position(1900, 100, 1080, 1920)), msg.getFirstShort());
}

void RType::Client::newBydosToRoom(const Utils::MessageParsed_s &msg)
{
    std::unique_lock<std::mutex> lock(*this->_mutex);
    auto it = this->_entities._entities.find(msg.getFirstShort());
    if (it != this->_entities._entities.end())
        return;
    this->_entities.addEntity(std::make_shared<Bydos>(Position(1900, 100, 1080, 1920), 1, Vector2d(-1, 0)), msg.getFirstShort());
}

void RType::Client::newTourreToRoom(const Utils::MessageParsed_s &msg)
{
    std::unique_lock<std::mutex> lock(*this->_mutex);
    auto it = this->_entities._entities.find(msg.getFirstShort());
    if (it != this->_entities._entities.end())
        return;
    this->_entities.addEntity(std::make_shared<Tourre>(Position(1900, 100, 1080, 1920), 1, Vector2d(-1, 0)), msg.getFirstShort());
}

void RType::Client::removeAnEntity(const Utils::MessageParsed_s &msg)
{
    std::unique_lock<std::mutex> lock(*this->_mutex);
    this->_entities.removeEntity(msg.getFirstShort());
}

void RType::Client::newEnemyShoot(const Utils::MessageParsed_s &msg)
{
    std::unique_lock<std::mutex> lock(*this->_mutex);
    auto it = this->_entities._entities.find(msg.getFirstShort());
    if (it != this->_entities._entities.end())
        return;
    Position pos(-20, -20);
    AIShoot aiShoot(pos, pos);
    auto tmpShoot = aiShoot.shootLogic();
    this->_entities.addEntity(std::make_shared<ShotEntity>(tmpShoot, "../Assets/EntitiesSprites/tEnemyShot.png", false), msg.getFirstShort());
}

void RType::Client::setValues(const Utils::MessageParsed_s &msg)
{
    std::unique_lock<std::mutex> lock(*this->_mutex);
    auto find = this->_entities._entities.find(msg.getFirstShort());
    if (find == this->_entities._entities.end())
        return;
    if (find->second->getEntityType() == player) {
        std::shared_ptr<Player> playerCasted = std::dynamic_pointer_cast<Player>(find->second);
        playerCasted->setLife(msg.bytes[3]);
        this->_lifeBar->setLifeBarToPlayer(playerCasted);
    }
    if (find->second->getEntityType() == bydos) {
        std::shared_ptr<Bydos> bydosCasted = std::dynamic_pointer_cast<Bydos>(find->second);
        bydosCasted->setLife(msg.bytes[3]);
        this->_lifeBar->setLifeBarToBydos(bydosCasted); 
    }

    if (find->second->getEntityType() == tourre) {
        std::shared_ptr<Tourre> tourreCasted = std::dynamic_pointer_cast<Tourre>(find->second);
        tourreCasted->setLife(msg.bytes[3]);
        this->_lifeBar->setLifeBarToTourre(tourreCasted);
    }
}

void RType::Client::newMyShoot(const Utils::MessageParsed_s &msg)
{
    std::unique_lock<std::mutex> lock(*this->_mutex);
    auto it = this->_entities._entities.find(msg.getFirstShort());
    if (it != this->_entities._entities.end())
        return;
    Position pos(-20, -20);
    AIShoot aiShoot(pos, pos);
    auto tmpShoot = aiShoot.shootLogic();
    this->_entities.addEntity(std::make_shared<ShotEntity>(tmpShoot, "../Assets/shot.png", true), msg.getFirstShort());  
}

void RType::Client::newPercingShoot(const Utils::MessageParsed_s &msg)
{
    std::unique_lock<std::mutex> lock(*this->_mutex);
    auto it = this->_entities._entities.find(msg.getFirstShort());
    if (it != this->_entities._entities.end())
        return;
    Position pos(-20, -20);
    AIShoot aiShoot(pos, pos);
    auto tmpShoot = aiShoot.shootLogic();
    this->_entities.addEntity(std::make_shared<PiercingShotEntity>(tmpShoot), msg.getFirstShort());
}

sf::Sprite RType::Client::getSpriteFromEntity(std::shared_ptr<IEntity> entity, unsigned int id)
{
    sf::Sprite ret;
    int spriteFrame = entity->getEntitySpriteFrame() + 1;
    if (entity->getEntityType() == RType::EntityTypes::tourre) {
        ret.setTexture(this->_texture.tourreTexture);
        ret.setTextureRect(sf::Rect<int>(0, 420 * (spriteFrame - 1), 494, 420));
        ret.setScale(0.5, 0.5);
        ret.setPosition(entity->getPosition().getX(), entity->getPosition().getY());
    }
    if (entity->getEntityType() == RType::EntityTypes::bydosShoot) {
        ret.setTexture(this->_texture.enemyShotTexture);
        ret.setTextureRect(sf::Rect<int>(98 * (spriteFrame - 1), 0, 98, 92));
        ret.setScale(0.5, 0.5);
    }
    if (entity->getEntityType() == RType::EntityTypes::bydos) {
        ret.setTexture(this->_texture.bydosTexture);
        ret.setTextureRect(sf::Rect<int>(140 * (spriteFrame - 1), 0, 140, 132));
        ret.setScale(0.8, 0.8);
    }
    if (entity->getEntityType() == RType::EntityTypes::percingShoot) {
        ret.setTexture(this->_texture.piercingShotTexture);
        ret.setTextureRect(sf::Rect<int>(55 * (spriteFrame - 1), 0, 55, 50));
    }
    if (entity->getEntityType() == RType::EntityTypes::coin) {
        ret.setTexture(this->_texture.coinTexture);
        ret.setTextureRect(sf::Rect<int>(103 * (spriteFrame - 1), 0, 103, 130));
    }
    if (entity->getEntityType() == RType::EntityTypes::playerShoot) {
        ret.setTexture(this->_texture.playerShotTexture);
    }
    if (entity->getEntityType() == RType::EntityTypes::player && id == this->_actualId) {
        ret.setTexture(this->_texture.playerTexture);
        ret.setTextureRect(sf::Rect<int>(107 * (spriteFrame - 1), 0, 107, 98));
        // int r = rand() % 3;
        // if (r == 0)
            // ret.setTextureRect(sf::Rect<int>(107 * (spriteFrame - 1), 0, 107, 98));
        // else if (r == 1)
            // ret.setTextureRect(sf::Rect<int>(109 * (spriteFrame - 1), 106, 109, 89));
        // else
            // ret.setTextureRect(sf::Rect<int>(106 * (spriteFrame - 1), 201, 106, 99));
    }
    if (entity->getEntityType() == RType::EntityTypes::player && id != this->_actualId) {
        ret.setTexture(this->_texture.otherPlayerTexture);
        ret.setTextureRect(sf::Rect<int>(109 * (spriteFrame - 1), 0, 109, 98));
    }
    ret.setPosition(entity->getPosition().getX(), entity->getPosition().getY());
    return (ret);
}

void RType::Client::gameLoop()
{
    this->checkAsId();
    if (!this->_gameAsStarted) {
        // this->createRoom(1);
        this->_gameAsStarted = true;
    }
    auto msgKeyPressed = this->buildEmptyMsg(keyPressed);
    unsigned char actualIndex = 0;
    _window->clear();
    if (this->_level == 1) {
        this->_parallax.drawBackgroundParallax(this->_window);
        this->_parallax.drawParallax(this->_window);
    }
    if (this->_level == 2) {}
        this->_parallaxGnome.drawGnomeParallax(this->_window);
    this->_lifeBar->display(this->_window);
    for (auto &it : this->_entities._entities)
    this->_lifeBar->display(this->_window);   
    std::unique_lock<std::mutex> lock(*this->_mutex);
    for (auto &it : this->_entities._entities)
        this->_window->draw(this->getSpriteFromEntity(it.second, it.first));
    for (auto &it : this->_predictionCore._entities)
        this->_window->draw(this->getSpriteFromEntity(it.second, it.first));
    // std::cout << "Entities size is " << this->_entities._entities.size() << std::endl;
    lock.unlock();
    auto mousePos = sf::Mouse::getPosition(*this->_window);
    if (this->_mouseClicked) {
        this->_msgPanel.clickButtons(mousePos);
        this->_buttonList.clickButtons(mousePos);
    } else {
        this->_msgPanel.hoverButtons(mousePos);
        this->_buttonList.hoverButtons(mousePos);
    }
    this->_buttonList.displayButtons(this->_window);
    this->_popUp.display(this->_window);
    this->_msgPanel.display(this->_window);
    if (this->_msgPanel.needSendMessage()) {
        auto msgg = this->_msgPanel.sendMessage();
        msgg.senderIp = this->_serverIp;
        msgg.senderPort = this->_serverPort;
        this->_socket->send(msgg);
    }
    _window->display();
    this->setLifeBars();
    this->updateInputs();
    this->_predicate->PredicatePlayer(this->_actualId, 100);
    lock.lock();
    this->_predicate->PredicateOtherEntities();
    lock.unlock();
    this->sendInputs();
}

void RType::Client::changeTypeEntityAndMove(const Utils::MessageParsed_s &msg, std::unordered_map<unsigned short, std::shared_ptr<IEntity>>::iterator &it)
{
    std::unique_lock<std::mutex> lock(*this->_mutex);
    if (it == this->_entities._entities.end())
        return;
    Utils::MessageParsed_s NewMsg = this->buildEmptyMsg(entityType);
    NewMsg.setFirstShort(msg.getFirstShort());
    // NewMsg.bytes[3] = msg.bytes[6];
    NewMsg.setSecondShort(static_cast<unsigned short>(msg.bytes[6]));
    this->_entities._entities.erase(it);
    lock.unlock();
    this->setEntityType(NewMsg);
    return this->moveEntity(msg);
}

void RType::Client::sendInputs()
{
    auto msgKeyPressed = this->buildEmptyMsg(keyPressed);
    unsigned char actualIndex = 0;
    auto clock = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::microseconds>(clock - this->_sendInputTime).count() < 10)
        return;
    this->_sendInputTime = clock;
    while (!this->_inputs.empty()) {
        if (actualIndex > 5) {
            this->_socket->send(msgKeyPressed);
            actualIndex = 0;
        }
        msgKeyPressed.bytes[actualIndex] = static_cast<unsigned short>(this->_inputs.back());
        this->_inputs.pop_back();
        actualIndex++;
    }
    if (actualIndex > 0) {
        msgKeyPressed.bytes[actualIndex] = 255;
        this->_socket->send(msgKeyPressed);
    }
    this->_parallax.drawScreenFX(this->_window);
}

void RType::Client::syncNbOfEntities(const Utils::MessageParsed_s &msg)
{
    unsigned short actSize = static_cast<unsigned short>(this->_entities._entities.size());
    unsigned short desiredSize = msg.getFirstShort();
    std::unique_lock<std::mutex> lock(*this->_mutex);
    for (; actSize > msg.getFirstShort(); actSize--)
        this->_entities.removeEntity(actSize);
}

void RType::Client::setLifeBars()
{
    std::unique_lock<std::mutex> lock(*this->_mutex);
    for (auto &it : this->_entities._entities) {
        if (it.second->getEntityType() == bydos) {
            std::shared_ptr<Bydos> bydosCasted = std::dynamic_pointer_cast<Bydos>(it.second);
            this->_lifeBar->setLifeBarToBydos(bydosCasted); 
        }
        if (it.second->getEntityType() == player) {
            std::shared_ptr<Player> playerCasted = std::dynamic_pointer_cast<Player>(it.second);
            this->_lifeBar->setLifeBarToPlayer(playerCasted);    
        }
    }
}

void RType::Client::displayMenu()
{
    this->handleInputs();
    this->_window->clear(sf::Color::Black);
    this->_menu.displayMenu(this->_window, this->_mouseClicked);
    if (this->_menu.needToSendMessage()) {
        auto msg = this->_menu.sendMsg();
        msg.senderIp = this->_serverIp;
        msg.senderPort = this->_serverPort;
        this->_quittedRoom = false;
        this->_socket->send(msg);
    }
    if (this->_menu.closeMenu() && !this->_quittedRoom) {
        this->checkAsId();
        this->_actualScreen = game;
    }
    this->_popUp.display(this->_window);
    this->_window->display();
}

void RType::Client::quitActualRoom()
{
    if (this->_actualId == -1) {
        #ifdef __unix__
            if (this->_serverPid != -1) {
                kill(this->_serverPid, SIGINT);
                kill(this->_serverPid, SIGTERM);
            }
        #endif
        return std::exit(0);
    }
    auto msg = this->buildEmptyMsg(playerDeconnected);
    msg.bytes[0] = this->_menu.getRoomId();
    msg.bytes[1] = this->_actualId;
    this->_socket->send(msg);
}


void RType::Client::newMessage(const Utils::MessageParsed_s &msg)
{
    std::cout << "New message" << std::endl;
    this->_popUp.setText(this->_msgPanel.decyptMessage(msg));
}
