add_executable(StdWStringSerializerTest
    StdWStringSerializerTest.cpp
)
target_include_directories(StdWStringSerializerTest PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)
add_test(
    NAME StdWStringSerializerTest
    COMMAND StdWStringSerializerTest
)


add_executable(StdVectorSerializerTest
    StdVectorSerializerTest.cpp
)
target_include_directories(StdVectorSerializerTest PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)
add_test(
    NAME StdVectorSerializerTest
    COMMAND StdVectorSerializerTest
)


add_executable(StdMapSerializerTest
    StdMapSerializerTest.cpp
)
target_include_directories(StdMapSerializerTest PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)
add_test(
    NAME StdMapSerializerTest
    COMMAND StdMapSerializerTest
)


add_executable(NetworkAddressTest
    NetworkAddressTest.cpp
    ${PROJECT_SOURCE_DIR}/src/utils/NetworkAddress.cpp
)
target_include_directories(NetworkAddressTest PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)
add_test(
    NAME NetworkAddressTest
    COMMAND NetworkAddressTest
)


add_executable(ChannelTest
    ChannelTest.cpp
    ${PROJECT_SOURCE_DIR}/src/network/Channel.cpp
    ${PROJECT_SOURCE_DIR}/src/network/Socket.cpp
    ${PROJECT_SOURCE_DIR}/src/utils/NetworkAddress.cpp
)
target_include_directories(ChannelTest PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)
target_link_libraries(ChannelTest PRIVATE Ws2_32.lib)
add_test(
    NAME ChannelTest
    COMMAND ChannelTest
)


add_executable(GameEventSerializerTest
    GameEventSerializerTest.cpp
    ${PROJECT_SOURCE_DIR}/src/GameSession.cpp
    ${PROJECT_SOURCE_DIR}/src/serializers/GameEventSerializer.cpp
    ${PROJECT_SOURCE_DIR}/src/serializers/GameSessionSerializer.cpp
    ${PROJECT_SOURCE_DIR}/src/serializers/GameSetSerializer.cpp
    ${PROJECT_SOURCE_DIR}/src/serializers/ParticipantSerializer.cpp
)
target_include_directories(GameEventSerializerTest PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)
target_compile_definitions(GameEventSerializerTest PRIVATE UNICODE)

add_test(
    NAME GameEventSerializerTest
    COMMAND GameEventSerializerTest
)


add_executable(GameSessionSerializerTest
    GameSessionSerializerTest.cpp
    ${PROJECT_SOURCE_DIR}/src/GameSession.cpp
    ${PROJECT_SOURCE_DIR}/src/serializers/GameSessionSerializer.cpp
    ${PROJECT_SOURCE_DIR}/src/serializers/GameSetSerializer.cpp
    ${PROJECT_SOURCE_DIR}/src/serializers/ParticipantSerializer.cpp
)
target_include_directories(GameSessionSerializerTest PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)
target_compile_definitions(GameSessionSerializerTest PRIVATE UNICODE)

add_test(
    NAME GameSessionSerializerTest
    COMMAND GameSessionSerializerTest
)