target_include_directories( ${TARGET_NAME} PUBLIC ${OPENGL_INCLUDE_DIR} )
target_include_directories( ${TARGET_NAME} PUBLIC ${GLFW_INCLUDE_DIRS} )
target_include_directories( ${TARGET_NAME} PUBLIC ${CMAKE_SOURCE_DIR} )
target_include_directories( ${TARGET_NAME} PUBLIC /usr/local/include/ )

# GLAD
add_library(GLAD third_party/glad.c)
target_include_directories(GLAD PUBLIC /usr/local/include)

# STB_IMAGE
add_library(STB_IMAGE third_party/stb_image.cpp)
target_include_directories(STB_IMAGE PUBLIC ${CMAKE_SOURCE_DIR}/third_party)

target_link_libraries(${TARGET_NAME} ${OPENGL_opengl_LIBRARY} ${GLFW_LIBRARIES})

target_link_libraries(${TARGET_NAME} ${OPENGL_glu_LIBRARY} ${OPENGL_glx_LIBRARY})

target_link_libraries(${TARGET_NAME} ${ASSIMP_LIBRARIES})

target_link_libraries(${TARGET_NAME} GLAD STB_IMAGE)

message( "GLFW Include : " ${GLFW_INCLUDE_DIRS} )
message( "GLFW Libs : " ${GLFW_LIBRARIES} )
message( "ASSIMP Include :" ${ASSIMP_INCLUDE_DIRS})
message( "ASSIMP Libs: " ${ASSIMP_LIBRARIES})