
./vcpkg export cryptopp:x64-linux --zip --output=vcpkg-x64-linux-1
./vcpkg install gtest:x64-linux cryptopp:x64-linux
./vcpkg install gtest:arm64-linux cryptopp:arm64-linux
./vcpkg export gtest:x64-linux cryptopp:x64-linux --zip --output=vcpkg-x64-linux
./vcpkg.exe install gtest:x64-windows cryptopp:x64-windows
./vcpkg.exe export gtest:x64-windows cryptopp:x64-windows --zip --output=vcpkg-x64-windows