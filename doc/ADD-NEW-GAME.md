# Adding a new game to the arcade

To add a new game to the arcade, follow these steps:

## 1. Game library interface

All game libraries in the arcade are based on the same interfaces. These interfaces are prefixed with the letter 'I', such as **IGameModule**, **IPixels** or **ITexts**. You can find these interfaces in the [Arcade GitHub repository](https://github.com/milimarg/Arcade-Groupes).

## 2. Implement the game library

Create a new game library that implements the necessary interfaces. This library should contain the game logic, including pixel updating using the IPixels implementation, input handling, and game mechanics. Ensure that the compiled library is compatible with the arcade's runtime environment.

Make sure to implement an extern C following this exact format:

```cpp
extern "C" {
    std::string getType() {
        return "game";
    }

    std::unique_ptr<arcade::IGameModule> entryPoint() {
        return std::make_unique<arcade::GameLibraryName>();
    }
}
```

## 3. Compile the game library

Compile the game library into a shared object (`.so`) file.

## 4. Update the library folder

Place the compiled shared object in the `./lib` folder of the arcade. This allows the arcade to detect and load the new game library at runtime.

## 5. Test the integration

Test the integration of the new game library with the arcade. Launch the arcade and verify that the new game appears in the list of available games in the main menu. Ensure that the game functions correctly and is playable.

## 6. Documentation and resources

Provide documentation for the new game, including instructions on how to play and any additional information that players could need.
