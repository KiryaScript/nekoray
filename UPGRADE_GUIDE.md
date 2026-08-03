# Upgrade Guide to NekoRay 2026 Standards

This guide helps you upgrade your NekoRay development environment and codebase to meet 2026 standards.

## Prerequisites

### System Requirements

- **Operating System**: 
  - Windows 10 21H2+ or Windows 11
  - macOS 12+ (Monterey or later)
  - Linux with glibc 2.35+ (Ubuntu 22.04+, Fedora 36+, etc.)

- **Compiler**:
  - GCC 13+ 
  - Clang 17+
  - MSVC 2022 (17.8+)

- **Build Tools**:
  - CMake 3.28+
  - Ninja 1.11+ (recommended)

- **Qt Framework**:
  - Qt 6.5+ LTS (recommended: 6.6+)
  - Required modules: Widgets, Network, Svg, LinguistTools, Concurrent

## Breaking Changes

### C++ Standard Upgrade (C++17 → C++23)

**What Changed:**
The project now requires C++23 standard.

**Migration Steps:**

1. Update your compiler flags:
   ```cmake
   set(CMAKE_CXX_STANDARD 23)
   ```

2. Review deprecated features:
   - Replace `std::auto_ptr` (already removed in C++17)
   - Use `std::format` instead of `fmt::format` where appropriate
   - Adopt `std::expected` for error handling (C++23)

3. New features to leverage:
   - Modules (when supported)
   - `std::print` for console output
   - Enhanced ranges library
   - `if consteval` for compile-time branching

### Qt 5 → Qt 6 Migration

**What Changed:**
Default Qt version upgraded from 5.x to 6.5+.

**Migration Steps:**

1. Update CMake configuration:
   ```cmake
   # Old
   find_package(Qt5 REQUIRED COMPONENTS Widgets Network)
   
   # New
   find_package(Qt6 REQUIRED COMPONENTS Widgets Network Svg LinguistTools Concurrent)
   ```

2. Code changes:
   ```cpp
   // Old Qt 5
   QApplication::setAttribute(Qt::AA_DisableWindowContextHelpButton);
   
   // New Qt 6 - removed, behavior is default
   // Just remove this line
   ```

3. API updates:
   - `QRegExp` → `QRegularExpression`
   - `QDesktopWidget` → `QScreen` (removed in Qt 6)
   - `qInstallMessageHandler` signature changed

4. Build system:
   ```cmake
   # Old
   qt5_create_translation(QM_FILES ...)
   
   # New
   qt_add_lupdate(nekoray TS_FILES ...)
   qt_add_lrelease(nekoray TS_FILES ...)
   ```

### CMake Minimum Version (3.5 → 3.28)

**What Changed:**
Minimum CMake version increased to 3.28.

**Migration Steps:**

1. Update `CMakeLists.txt`:
   ```cmake
   cmake_minimum_required(VERSION 3.28)
   ```

2. Use modern CMake practices:
   - Target-based commands
   - Generator expressions
   - FetchContent for dependencies

## Step-by-Step Upgrade Process

### 1. Backup Your Work

```bash
git checkout -b backup-before-upgrade
git push origin backup-before-upgrade
```

### 2. Update Development Environment

#### Linux (Ubuntu/Debian)

```bash
# Install updated toolchain
sudo apt update
sudo apt install build-essential cmake ninja-build

# Install Qt 6
sudo apt install qt6-base-dev qt6-svg-dev libqt6svg6-dev

# Install clang-format and clang-tidy
sudo apt install clang-format-17 clang-tidy-17
```

#### macOS

```bash
# Using Homebrew
brew install cmake ninja qt protobuf grpc yaml-cpp

# Link Qt
brew link qt6
```

#### Windows

```powershell
# Install Chocolatey packages
choco install -y cmake ninja visualstudio2022community

# Download Qt Online Installer
# https://download.qt.io/official_releases/qt/
```

### 3. Update Project Configuration

Replace your `CMakeLists.txt` header with:

```cmake
cmake_minimum_required(VERSION 3.28)

project(nekoray VERSION 3.26 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
```

### 4. Fix Compiler Errors

Common issues and fixes:

**Issue:** `setAttribute` is deprecated
```cpp
// Remove these lines for Qt 6
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QApplication::setAttribute(Qt::AA_DisableWindowContextHelpButton);
#endif
```

**Issue:** Missing Qt modules
```cmake
# Add to find_package
find_package(Qt6 REQUIRED COMPONENTS 
    Widgets 
    Network 
    Svg 
    LinguistTools 
    Concurrent
)
```

### 5. Run Code Formatting

```bash
# Format all C++ files
find . -name "*.cpp" -o -name "*.hpp" | xargs clang-format -i

# Or use the provided script
./libs/format_cpp.sh
```

### 6. Build and Test

```bash
# Clean previous builds
rm -rf build/

# Configure
cmake -B build \
  -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug \
  -DQT_VERSION_MAJOR=6

# Build
cmake --build build --parallel $(nproc)

# Test
cd build && ctest --output-on-failure
```

## Common Issues and Solutions

### Issue: "Qt6 not found"

**Solution:**
Ensure Qt 6 is installed and in CMAKE_PREFIX_PATH:
```bash
export CMAKE_PREFIX_PATH=/path/to/qt6:$CMAKE_PREFIX_PATH
```

### Issue: "C++23 feature not supported"

**Solution:**
Update your compiler to a version that supports C++23:
- GCC 13+
- Clang 17+
- MSVC 2022 17.8+

### Issue: "linker errors with Qt modules"

**Solution:**
Add missing modules to `target_link_libraries`:
```cmake
target_link_libraries(nekoray PRIVATE
    Qt6::Widgets
    Qt6::Network
    Qt6::Svg
    Qt6::Concurrent
)
```

## Post-Upgrade Checklist

- [ ] Project builds without errors
- [ ] All tests pass
- [ ] No runtime warnings
- [ ] UI renders correctly
- [ ] All features work as expected
- [ ] Performance is acceptable
- [ ] Memory usage is normal

## Rollback Plan

If you need to rollback:

```bash
# Restore previous version
git checkout backup-before-upgrade

# Or checkout specific tag
git checkout v3.26
```

## Additional Resources

- [Qt 6 Migration Guide](https://doc.qt.io/qt-6/migrationguide.html)
- [C++23 Features](https://en.cppreference.com/w/cpp/23)
- [Modern CMake](https://cliutils.gitlab.io/modern-cmake/)
- [NekoRay Code Style Guide](CODE_STYLE.md)

## Support

If you encounter issues during upgrade:

1. Check existing issues on GitHub
2. Review the documentation
3. Ask in community channels
4. Create a detailed issue report

---

Last updated: 2024
Version: 1.0
