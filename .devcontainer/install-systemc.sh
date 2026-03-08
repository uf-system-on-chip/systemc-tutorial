#!/bin/bash
set -e

echo "🔨 Installing SystemC 2.3.3..."

# Update package lists
apt-get update
apt-get install -y --no-install-recommends \
    curl \
    wget \
    ca-certificates

# Create a temporary directory for SystemC build
SYSTEMC_BUILD_DIR=$(mktemp -d)
trap "rm -rf $SYSTEMC_BUILD_DIR" EXIT

cd "$SYSTEMC_BUILD_DIR"

# Download SystemC 2.3.3
echo "📥 Downloading SystemC 2.3.3..."
wget https://www.accellera.org/images/downloads/standards/systemc/systemc-2.3.3.tar.gz -q -O systemc-2.3.3.tar.gz

# Extract
tar -xzf systemc-2.3.3.tar.gz

# Build and install
cd systemc-2.3.3
mkdir -p build
cd build

echo "⚙️  Configuring and building SystemC..."
../configure --prefix=/usr/local/systemc-2.3.3 CXXFLAGS="-std=c++17" > /dev/null 2>&1
make -j$(nproc) > /dev/null 2>&1

echo "📦 Installing SystemC to /usr/local/systemc-2.3.3..."
make install > /dev/null 2>&1

# Verify installation
if [ -f "/usr/local/systemc-2.3.3/lib-linux64/libsystemc.a" ]; then
    echo "✅ SystemC 2.3.3 installed successfully!"
else
    echo "❌ SystemC installation failed"
    exit 1
fi

echo "🎉 Development environment is ready!"
