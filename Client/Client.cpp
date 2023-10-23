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
    this->_actualScreen = Screens::game;
    this->_gameAsStarted = false;
    this->_inputs = {};
    this->_serverIp = av[1];
    this->_serverPort = std::stoi(av[2]);
    this->_mutex = std::make_unique<std::mutex>();
    this->_window = std::make_unique<sf::RenderWindow>(sf::VideoMode::getDesktopMode(), "R-Type", sf::Style::Fullscreen);
    // if (this->_music.openFromFile("../Assets/music.ogg") != -1)
        // this->_music.play();
    this->_socket = std::make_unique<Utils::SocketHandler>("127.0.0.1", 4001 + std::rand() % 3000, std::list<int>({keyPressed, entityType, playerPing, newPlayerConnected, givePlayerId, destroyedRoom, serverStop, entityType, removeEntity, playerDeconnected, newRoomIsCreated, playerGetId, givePlayerId}));
    this->_threadIsOpen = true;
    this->_actualId = -1;
    this->_predicate = std::make_unique<Prediction>(this->_entities, this->_inputs);
    this->_infosThread = std::make_unique<std::thread>(&RType::Client::infosThread, this);
    this->run();
}

RType::Client::~Client()
{
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
                    this->_inputs.push_back(Events::CloseWindow);
                    break;
                case (sf::Keyboard::Space) :
                    if (!this->shooting) {
                        this->shotTime = std::chrono::steady_clock::now();
                        this->shooting = true;
                    }
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
            }
        }
    }
}

void RType::Client::run()
{
    while (_window->isOpen()) {
        switch (this->_actualScreen)
        {
        case game:
            this->gameLoop();
            break;
        }
    }
}

void RType::Client::infosThread()
{
    while (this->_threadIsOpen) {
        Utils::MessageParsed_s msg = this->_socket->receive();
        auto it = this->_commands.find(msg.msgType);
        if (it == this->_commands.end()) {
            std::cout << "Get an unhandled message " << static_cast<int>(msg.msgType) << std::endl;
            continue;
        }
        (this->*it->second)(msg);
    }
}

void RType::Client::sendPing(const Utils::MessageParsed_s &recMsg)
{
    auto msg = this->buildEmptyMsg(playerPing);
    this->_socket->send(msg);
    std::cout << "Ping sended..." << std::endl;
}


void RType::Client::handleNonAuthorized(const Utils::MessageParsed_s &msg)
{
    if (msg.bytes[2] == newRoomIsCreated) {
        this->_mutex->lock();
        this->_actualRoom = 0;
        this->_mutex->unlock();
        return this->joinRoom(1);
    }
    std::cout << "Unauthorized " << static_cast<int>(msg.bytes[0]) << std::endl;
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
    std::cout << "New player connected !!" << std::endl;
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
    // if (!checkAsId())
    //     return;
    std::unique_lock<std::mutex> lock(*this->_mutex);
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
    // std::cout << "Entity " << msg.getThirdShort() << " moves x = " << msg.getFirstShort() << " y = " << msg.getSecondShort() << std::endl; 
}

void RType::Client::quitRoom(const Utils::MessageParsed_s &msg)
{
    (void)msg;
    this->_actualId = -1;
    this->_threadIsOpen = false;
    this->_window->close();
    exit(0);
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
    }
    std::cout << "Unknown entity type " << (msg.getSecondShort()) << std::endl;
}

void RType::Client::newBydosToRoom(const Utils::MessageParsed_s &msg)
{
    auto it = this->_entities._entities.find(msg.getFirstShort());
    if (it != this->_entities._entities.end()) {
        // std::cout << "Already in core with id " << msg.getFirstShort() << std::endl;
        return;
    }
    std::unique_lock<std::mutex> lock(*this->_mutex);
    this->_entities.addEntity(std::make_shared<Bydos>(Position(1900, 100, 1080, 1920), 1, Vector2d(-1, 0)), msg.getFirstShort());
}

void RType::Client::newTourreToRoom(const Utils::MessageParsed_s &msg)
{
    auto it = this->_entities._entities.find(msg.getFirstShort());
    if (it != this->_entities._entities.end()) {
        // std::cout << "Already in core with id " << msg.getFirstShort() << std::endl;
        return;
    }
    std::unique_lock<std::mutex> lock(*this->_mutex);
    this->_entities.addEntity(std::make_shared<Tourre>(Position(1900, 100, 1080, 1920), 1, Vector2d(-1, 0)), msg.getFirstShort());
}

void RType::Client::removeAnEntity(const Utils::MessageParsed_s &msg)
{
    std::unique_lock<std::mutex> lock(*this->_mutex);
    std::cout << "Remove Entity" << std::endl;
    this->_entities.removeEntity(msg.getFirstShort());
}

void RType::Client::newEnemyShoot(const Utils::MessageParsed_s &msg)
{
    auto it = this->_entities._entities.find(msg.getFirstShort());
    if (it != this->_entities._entities.end()) {
        // std::cout << "Already in core with id " << msg.getFirstShort() << std::endl;
        return;
    }
    std::unique_lock<std::mutex> lock(*this->_mutex);
    Position pos(-20, -20);
    AIShoot aiShoot(pos, pos);
    auto tmpShoot = aiShoot.shootLogic();
    this->_entities.addEntity(std::make_shared<ShotEntity>(tmpShoot, "../Assets/EntitiesSprites/tEnemyShot.png", false), msg.getFirstShort());
}

void RType::Client::setValues(const Utils::MessageParsed_s &msg)
{
    auto find = this->_entities._entities.find(msg.getFirstShort());
    if (find == this->_entities._entities.end())
        return;
    if (find->second->getEntityType() == player) {
        std::unique_lock<std::mutex> lock(*this->_mutex);
        std::shared_ptr<Player> playerCasted = std::dynamic_pointer_cast<Player>(find->second);
        playerCasted->setLife(msg.bytes[3]);
        this->_lifeBar->setLifeBarToPlayer(playerCasted);
    }
    if (find->second->getEntityType() == bydos) {
        std::unique_lock<std::mutex> lock(*this->_mutex);
        std::shared_ptr<Bydos> bydosCasted = std::dynamic_pointer_cast<Bydos>(find->second);
        bydosCasted->setLife(msg.bytes[3]);
        this->_lifeBar->setLifeBarToBydos(bydosCasted); 
    }

    if (find->second->getEntityType() == tourre) {
        std::unique_lock<std::mutex> lock(*this->_mutex);
        std::shared_ptr<Tourre> tourreCasted = std::dynamic_pointer_cast<Tourre>(find->second);
        tourreCasted->setLife(msg.bytes[3]);
        this->_lifeBar->setLifeBarToTourre(tourreCasted);
    }
}

void RType::Client::newMyShoot(const Utils::MessageParsed_s &msg)
{
    auto it = this->_entities._entities.find(msg.getFirstShort());
    if (it != this->_entities._entities.end()) {
        // std::cout << "Already in core with id " << msg.getFirstShort() << std::endl;
        return;
    }
    std::unique_lock<std::mutex> lock(*this->_mutex);
    Position pos(-20, -20);
    AIShoot aiShoot(pos, pos);
    auto tmpShoot = aiShoot.shootLogic();
    this->_entities.addEntity(std::make_shared<ShotEntity>(tmpShoot, "../Assets/shot.png", true), msg.getFirstShort());  
}

void RType::Client::newPercingShoot(const Utils::MessageParsed_s &msg)
{
    auto it = this->_entities._entities.find(msg.getFirstShort());
    if (it != this->_entities._entities.end()) {
        // std::cout << "Already in core with id " << msg.getFirstShort() << std::endl;
        return;
    }
    std::unique_lock<std::mutex> lock(*this->_mutex);
    Position pos(-20, -20);
    AIShoot aiShoot(pos, pos);
    auto tmpShoot = aiShoot.shootLogic();
    this->_entities.addEntity(std::make_shared<PiercingShotEntity>(tmpShoot), msg.getFirstShort());
}

sf::Sprite RType::Client::getSpriteFromEntity(std::shared_ptr<IEntity> entity, unsigned int id)
{
    sf::Sprite ret;
    int spriteFrame = entity->getEntitySpriteFrame() + 1;
    if (entity->getEntityType() == 6) {
        ret.setTexture(this->_texture.tourreTexture);
        ret.setTextureRect(sf::Rect<int>(0, 420 * (spriteFrame - 1), 494, 420));
        ret.setScale(0.5, 0.5);
        ret.setPosition(entity->getPosition().getX(), entity->getPosition().getY());
    }
    if (entity->getEntityType() == 5) {
        ret.setTexture(this->_texture.enemyShotTexture);
        ret.setTextureRect(sf::Rect<int>(98 * (spriteFrame - 1), 0, 98, 92));
        ret.setScale(0.5, 0.5);
    }
    if (entity->getEntityType() == 4) {
        ret.setTexture(this->_texture.bydosTexture);
        ret.setTextureRect(sf::Rect<int>(140 * (spriteFrame - 1), 0, 140, 132));
        ret.setScale(0.8, 0.8);
    }
    if (entity->getEntityType() == 3) {
        ret.setTexture(this->_texture.piercingShotTexture);
        ret.setTextureRect(sf::Rect<int>(55 * (spriteFrame - 1), 0, 55, 50));
    }
    if (entity->getEntityType() == 2) {
        ret.setTexture(this->_texture.playerShotTexture);
    }
    if (entity->getEntityType() == 1 && id == this->_actualId) {
        ret.setTexture(this->_texture.playerTexture);
        ret.setTextureRect(sf::Rect<int>(106 * (spriteFrame - 1), 0, 106, 98));
    }
    if (entity->getEntityType() == 1 && id != this->_actualId) {
        ret.setTexture(this->_texture.otherPlayerTexture);
        ret.setTextureRect(sf::Rect<int>(109 * (spriteFrame - 1), 0, 109, 98));
    }
    ret.setPosition(entity->getPosition().getX(), entity->getPosition().getY());
    return (ret);
}

void RType::Client::gameLoop()
{
    if (!this->_gameAsStarted) {
        this->createRoom(1);
        this->_gameAsStarted = true;
    }
    _window->clear();
    this->_lifeBar->display(this->_window);   
    std::unique_lock<std::mutex> lock(*this->_mutex);
    for (auto &it : this->_entities._entities) {
        this->_window->draw(this->getSpriteFromEntity(it.second, it.first));
    }
    lock.unlock();
    _window->display();
    this->updateInputs();
    // this->_predicate->PredicatePlayer(this->_actualId, 100);
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
    // if (!this->_inputs.empty())
    //     std::cout << "Inputs size " << this->_inputs.size() << std::endl;
    // if (this->_inputs.size() < 5)
    //     return;
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
    this->_socket->sendAllMessagesFromImportant();
}