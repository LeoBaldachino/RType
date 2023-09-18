#include "entity.hpp"
#include "sparse_array.hpp"
#include "component.hpp"
#include <unordered_map>
#include <typeindex>
#include <memory>

class Registry {
    private:
        SparseArray<Entity> entities;
        size_t nextId = 0;
        std::unordered_map<std::type_index, std::unique_ptr<Component>> components;

    public:
        Registry() = default;
        Registry(const Registry&) = default;
        Registry(Registry&&) = default;
        Registry& operator=(const Registry&) = default;
        Registry& operator=(Registry&&) = default;
        ~Registry() = default;

        Entity create() {
            Entity entity(nextId++);
            entities.add(entity);
            return entity;
        }

        void destroy(Entity entity) {
            entities.remove(entity);
        }

        Entity get(size_t id) {
            return entities[id];
        }

        size_t size() const {
            return entities.size();
        }

        template<typename T>
        T* get_components() {
            std::type_index ti = std::type_index(typeid(T));
            return static_cast<T*>(components[ti]);
        }
        
};