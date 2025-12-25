find_package(Boost REQUIRED COMPONENTS thread)
find_package(OpenSSL REQUIRED)
find_package(Protobuf CONFIG)
find_package(absl REQUIRED)
find_package(Qt5 COMPONENTS Core REQUIRED)

add_library(core_lib STATIC
        src/chat_core/session.cc
        src/network/client.cc
        src/network/server.cc
        src/crypto/cert_gen.cc
        src/util/message.pb.cc
)
# Needs to be PUBLIC, so that any other target linking against core_lib will also get its include directory
# added to their search paths (PRIVATE will prevent that from happening).
target_include_directories(core_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(core_lib PUBLIC
        Boost::thread
        OpenSSL::SSL
        OpenSSL::Crypto
        Qt5::Core
        protobuf::libprotobuf
        absl::base
        absl::strings
        absl::synchronization
        absl::time
)