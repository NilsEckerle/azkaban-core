#!/bin/bash
# scripts/build_sqlcipher.sh

SQLCIPHER_VERSION="v4.8.0"
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
THIRD_PARTY_DIR="$PROJECT_ROOT/third/sqlcipher"

# Color codes for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

print_status() {
    echo -e "${GREEN}[INFO]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

# Create directory structure
print_status "Creating directory structure..."
mkdir -p $THIRD_PARTY_DIR/{lib,include}

# Clean up existing build directory
if [ -d "build_sqlcipher" ]; then
    print_warning "Removing existing build directory..."
    rm -rf build_sqlcipher
fi

mkdir -p build_sqlcipher
cd build_sqlcipher

# Clone SQLCipher
print_status "Cloning SQLCipher $SQLCIPHER_VERSION..."
git clone --depth 1 --branch $SQLCIPHER_VERSION https://github.com/sqlcipher/sqlcipher.git
cd sqlcipher

# Set required SQLCipher flags
SQLCIPHER_CFLAGS="-DSQLITE_HAS_CODEC"
SQLCIPHER_CFLAGS="$SQLCIPHER_CFLAGS -DSQLCIPHER_CRYPTO_OPENSSL"
SQLCIPHER_CFLAGS="$SQLCIPHER_CFLAGS -DSQLITE_TEMP_STORE=2"
SQLCIPHER_CFLAGS="$SQLCIPHER_CFLAGS -DSQLITE_EXTRA_INIT=sqlcipher_extra_init"
SQLCIPHER_CFLAGS="$SQLCIPHER_CFLAGS -DSQLITE_EXTRA_SHUTDOWN=sqlcipher_extra_shutdown"

# Configure based on platform
print_status "Configuring SQLCipher for $OSTYPE..."

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    # Linux - build static library only
    CFLAGS="$SQLCIPHER_CFLAGS" \
    LDFLAGS="-lcrypto" \
    ./configure --disable-shared
elif [[ "$OSTYPE" == "darwin"* ]]; then
    # macOS - use CommonCrypto instead of OpenSSL
    SQLCIPHER_CFLAGS_MAC="-DSQLITE_HAS_CODEC"
    SQLCIPHER_CFLAGS_MAC="$SQLCIPHER_CFLAGS_MAC -DSQLCIPHER_CRYPTO_CC"
    SQLCIPHER_CFLAGS_MAC="$SQLCIPHER_CFLAGS_MAC -DSQLITE_TEMP_STORE=2"
    SQLCIPHER_CFLAGS_MAC="$SQLCIPHER_CFLAGS_MAC -DSQLITE_EXTRA_INIT=sqlcipher_extra_init"
    SQLCIPHER_CFLAGS_MAC="$SQLCIPHER_CFLAGS_MAC -DSQLITE_EXTRA_SHUTDOWN=sqlcipher_extra_shutdown"
    
    CFLAGS="$SQLCIPHER_CFLAGS_MAC" \
    ./configure --disable-shared
elif [[ "$OSTYPE" == "msys" ]] || [[ "$OSTYPE" == "cygwin" ]]; then
    # Windows - build static library only
    CFLAGS="$SQLCIPHER_CFLAGS" \
    LDFLAGS="-lcrypto -lws2_32" \
    ./configure --disable-shared
fi

# Check if configure succeeded
if [ $? -ne 0 ]; then
    print_error "Configuration failed!"
    exit 1
fi

# Build
print_status "Building SQLCipher..."
make

# Check if make succeeded
if [ $? -ne 0 ]; then
    print_error "Build failed!"
    exit 1
fi

# The static library should be created as libsqlcipher.a or libsqlite3.a
if [ -f ".libs/libsqlcipher.a" ]; then
    cp .libs/libsqlcipher.a "$THIRD_PARTY_DIR/lib/"
    print_status "Copied .libs/libsqlcipher.a"
elif [ -f "libsqlcipher.a" ]; then
    cp libsqlcipher.a "$THIRD_PARTY_DIR/lib/"
    print_status "Copied libsqlcipher.a"
elif [ -f ".libs/libsqlite3.a" ]; then
    # SQLCipher might name it libsqlite3.a
    cp .libs/libsqlite3.a "$THIRD_PARTY_DIR/lib/libsqlcipher.a"
    print_status "Copied .libs/libsqlite3.a as libsqlcipher.a"
elif [ -f "libsqlite3.a" ]; then
    cp libsqlite3.a "$THIRD_PARTY_DIR/lib/libsqlcipher.a"
    print_status "Copied libsqlite3.a as libsqlcipher.a"
elif [ -f "sqlite3.a" ]; then
    cp sqlite3.a "$THIRD_PARTY_DIR/lib/libsqlcipher.a"
    print_status "Copied sqlite3.a as libsqlcipher.a"
else
    print_error "Could not find static library!"
    print_status "Looking for library files..."
    find . -name "*.a" | head -10
    exit 1
fi

# Copy header - SQLCipher uses sqlite3.h
if [ -f "sqlite3.h" ]; then
    cp sqlite3.h "$THIRD_PARTY_DIR/include/"
    print_status "Copied sqlite3.h"
else
    print_error "Could not find sqlite3.h!"
    exit 1
fi

# Clean up
cd "$SCRIPT_DIR"
rm -rf build_sqlcipher

print_status "SQLCipher built successfully!"
print_status "Files installed to:"
print_status "  Header: $THIRD_PARTY_DIR/include/sqlite3.h"
print_status "  Library: $THIRD_PARTY_DIR/lib/libsqlcipher.a"

# Verify installation
if [ -f "$THIRD_PARTY_DIR/include/sqlite3.h" ] && [ -f "$THIRD_PARTY_DIR/lib/libsqlcipher.a" ]; then
    print_status "Installation verified successfully!"
    # Show file sizes for confirmation
    ls -lh "$THIRD_PARTY_DIR/include/sqlite3.h"
    ls -lh "$THIRD_PARTY_DIR/lib/libsqlcipher.a"
else
    print_error "Installation verification failed!"
    exit 1
fi
