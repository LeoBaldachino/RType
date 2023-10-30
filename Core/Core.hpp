/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** Core.hpp
*/

#pragma once
#include "../Entity/Player.hpp"
#include <unordered_map>
#include <memory>
#include <climits>
#include <list>
#include <mutex>

/**
 * @class Core
 * @brief Core class handles entities
 */
class Core {
    public:
        /**
         * @brief Construct a new Core object
         */
        Core() {};

        /**
         * @brief Destroy the Core object
         */
        ~Core() {};

        /**
         * @brief Add an entity to the core
         * @param entity The entity to add
         * @param index The index to add the entity at
         * @return true if the entity was added successfully, false otherwise
         */
        bool addEntity(const std::shared_ptr<IEntity> &entity, unsigned short index);

        /**
         * @brief Map of entities
         */
        std::unordered_map<unsigned short, std::shared_ptr<IEntity>> _entities;

        /**
         * @brief Get an available index
         * @return The available index
         */
        unsigned short getAvailabeIndex();

        /**
         * @brief Remove an entity by index
         * @param index The index of the entity to remove
         * @return true if the entity was removed successfully, false otherwise
         */
        bool removeEntity(unsigned short index);

        /**
         * @brief Remove an entity
         * @param entity The entity to remove
         * @return true if the entity was removed successfully, false otherwise
         */
        bool removeEntity(IEntity &entity);

        /**
         * @brief Schedule an entity for removal by index
         * @param index The index of the entity to schedule for removal
         * @return true if the entity was scheduled for removal successfully, false otherwise
         */
        bool removeEntityLater(unsigned short index);

        /**
         * @brief Schedule an entity for removal
         * @param entity The entity to schedule for removal
         * @return true if the entity was scheduled for removal successfully, false otherwise
         */
        bool removeEntityLater(IEntity &entity);

        /**
         * @brief Erase an entity
         */
        void eraseEntity(void);

        /**
         * @brief Get the queue of entities to erase
         * @return The queue of entities to erase
         */
        inline std::queue<unsigned short> getToErase() {return this->_erase;};

        /**
         * @brief Get the  id of the entity
         * 
         * @param entity the entity you want to know the id
         * @return unsigned short the id
         */
        unsigned short getEntityId(IEntity &entity);
    private:
        /**
         * @brief Queue of present indices
         */
        std::queue<unsigned short> _presentIndex;

        /**
         * @brief Queue of entities to erase
         */
        std::queue<unsigned short> _erase;

        /**
         * @brief Mutex for thread safety
         */
        std::mutex _mutex;
};
