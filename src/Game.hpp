#pragma once
#include <tuple>
#include <memory>
#include "Meta.hpp"

class Window;
class UpdateManager;
class WorldManager;

class Game {

    template<typename... Ts>
    class ModuleManager {
        template<typename T>
        using Module = std::unique_ptr<T>;
        
        std::tuple<Module<Ts>...> m_modules;
    public:
        void init() {
            (std::get<Module<Ts>>(m_modules).operator=(std::make_unique<Ts>()), ...);
        }

        template<typename T>
        T& getModule() {
            return *std::get<Module<T>>(m_modules);
        }
        
        ~ModuleManager() {
            TupleForwardFn<TupleReverse<std::tuple<Ts...>>>([&] <typename... Ts2> () {
                (std::get<Module<Ts2>>(m_modules).reset(), ...);
            });
        }
    };

    ModuleManager<
        UpdateManager, 
        Window, 
        WorldManager
    > m_modules;

public:
    Game();
    ~Game();

    void close();

    template<typename T>
    T& getModule() {
        return m_modules.getModule<T>();
    }
};

extern Game* game;