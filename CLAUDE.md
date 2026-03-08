# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

Geretchro is a 2D game engine running on a Raspberry Pi Pico microcontroller with a ST7789 TFT display (240x320, rendered at 160x120 with 2x pixel scaling). Built with PlatformIO and the Arduino framework.

## Build Commands

- **Build:** `pio run`
- **Upload to Pico:** `pio run -t upload`
- **Run tests:** `pio test`
- **Clean:** `pio run -t clean`
- **Serial monitor:** `pio device monitor`

## Architecture

The engine uses a **GameObject/Component** pattern. GameObjects hold a list of Components and always have a Transform. Components are heap-allocated via `GameObject::addComponent<T>()` which sets the back-pointer and calls `start()`.

### Main Loop (`src/main.cpp`)

Each frame runs in this order:
1. `Time::update()` — compute delta time
2. `InputSystem::update()` — read GPIO button states
3. `Graphics::clear()` — clear the offscreen canvas
4. `Game::update(dt)` — game logic
5. `Solver::step()` — physics collision resolution
6. `Renderer::draw()` — draw all registered sprites
7. `Graphics::present()` — push canvas to TFT display

### Key Systems (all namespace-based singletons)

- **Graphics** (`src/rendering/graphics.*`) — Wraps TFT_eSPI. Draws to an offscreen `TFT_eSprite` canvas at 160x120, then pushes to the 240x320 display with 2x scaling in `present()`.
- **Renderer** (`src/rendering/renderer.*`) — Maintains a list of registered `Sprite*` and calls their `draw()` each frame.
- **Solver** (`src/physics/solver.*`) — Maintains a list of registered `Collider*`. Runs AABB overlap detection and resolves collisions by splitting overlap equally between both objects.
- **InputSystem** (`src/inputSystem/inputSystem.*`) — Reads 4 directional buttons on GPIO pins 12-15 (INPUT_PULLUP, active low).
- **Time** (`src/time/time.*`) — Tracks frame delta time using `millis()`.
- **Game** (`src/game/game.*`) — Sets up game objects and runs per-frame game logic.

### Component Types

- **Component** (`src/core/component.h`) — Base class with virtual `start()`, `update(dt)`, `draw()`.
- **Transform** (`src/core/transform.h`) — Holds a `Math::Vector2 position`.
- **Sprite** (`src/rendering/components/sprite.h`) — Holds a `std::function<void()> drawFunction` lambda for custom rendering. Must be registered with `Renderer::registerSprite()`.
- **Collider / BoxCollider** (`src/physics/components/`) — `Collider` is abstract with `getBoundingBox()` returning `Math::Vector4` (x, y, w, h). Must be registered with `Solver::registerCollider()`.
- **Rigidbody** (`src/physics/components/rigidbody.h`) — Has Static/Dynamic body type, mass, gravity scale. Currently a stub.

### Math (`src/core/math/vectors.h`)

`Math::Vector2`, `Vector3`, `Vector4` structs with arithmetic operator overloads.

## Conventions

- Systems (Graphics, Renderer, Solver, InputSystem, Time) are implemented as namespaces with free functions, not classes.
- Components that participate in systems must be manually registered (e.g., `Renderer::registerSprite()`, `Solver::registerCollider()`).
- Function naming uses camelCase.
- Colors are 16-bit RGB565 constants in the `Colors` namespace.

## Hardware

- **Board:** Raspberry Pi Pico
- **Display:** ST7789 (SPI: MOSI=19, SCLK=18, CS=17, DC=20, RST=21)
- **Buttons:** GPIO 12 (left), 13 (down), 14 (right), 15 (up) — INPUT_PULLUP
