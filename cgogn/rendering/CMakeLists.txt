project(cgogn_rendering
	LANGUAGES CXX
)

find_package(Qt5 5.4.0 COMPONENTS Widgets REQUIRED)

if (Qt5Widgets_VERSION VERSION_GREATER 5.5.99)
	set(HEADER_W_QT56
	transparency_shaders/shader_transparent_quad.h
	transparency_shaders/shader_transparent_flat.h
	transparency_shaders/shader_transparent_phong.h
	transparency_shaders/shader_transparent_volumes.h
	transparency_shaders/shader_copy_depth.h
	transparency_drawer.h
	transparency_volume_drawer.h
	)

	set(SOURCE_W_QT56
	transparency_shaders/shader_transparent_quad.cpp
	transparency_shaders/shader_transparent_flat.cpp
	transparency_shaders/shader_transparent_phong.cpp
	transparency_shaders/shader_transparent_volumes.cpp
	transparency_shaders/shader_copy_depth.cpp
	transparency_drawer.cpp
	transparency_volume_drawer.cpp
	)
else()
	message(WARNING "Qt version < 5.6 : not compiling transparency rendering (need MRT FBO)")
endif()


set(HEADER_FILES
	dll.h
	shaders/vbo.h
	shaders/shader_program.h
	shaders/shader_simple_color.h
	shaders/shader_color_per_vertex.h
	shaders/shader_scalar_per_vertex.h
	shaders/shader_flat.h
	shaders/shader_vector_per_vertex.h
	shaders/shader_phong.h
	shaders/shader_bold_line.h
	shaders/shader_round_point.h
	shaders/shader_point_sprite.h
	shaders/shader_explode_volumes.h
	shaders/shader_explode_volumes_line.h
	shaders/shader_texture.h
	drawer.h
	topo_drawer.h
	volume_drawer.h
	map_render.h
	wall_paper.h
	frame_manipulator.h
	${HEADER_W_QT56}
)

set(SOURCE_FILES
	shaders/shader_program.cpp
	shaders/shader_simple_color.cpp
	shaders/shader_color_per_vertex.cpp
	shaders/shader_scalar_per_vertex.cpp
	shaders/shader_flat.cpp
	shaders/shader_vector_per_vertex.cpp
	shaders/shader_phong.cpp
	shaders/shader_bold_line.cpp
	shaders/shader_round_point.cpp
	shaders/shader_point_sprite.cpp
	shaders/shader_explode_volumes.cpp
	shaders/shader_explode_volumes_line.cpp
	shaders/shader_texture.cpp
	drawer.cpp
	topo_drawer.cpp
	volume_drawer.cpp
	map_render.cpp
	wall_paper.cpp
	frame_manipulator.cpp
	${SOURCE_W_QT56}
)

add_library(${PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "_d")
target_compile_definitions(${PROJECT_NAME} PRIVATE "-DCGOGN_RENDERING_DLL_EXPORT")

target_include_directories(${PROJECT_NAME} PUBLIC
	$<BUILD_INTERFACE:${CGOGN_THIRDPARTY_QOGLVIEWER_INCLUDE_DIR}>
	$<BUILD_INTERFACE:${CGOGN_SOURCE_DIR}>
	$<BUILD_INTERFACE:${CGOGN_THIRDPARTY_TINYXML2_INCLUDE_DIR}>
	$<INSTALL_INTERFACE:include>
)

target_link_libraries(${PROJECT_NAME} cgogn_core cgogn_geometry ${Qt5Widgets_LIBRARIES})

file(GLOB HEADERS "." "*.h")
install(FILES ${HEADERS}
	DESTINATION include/cgogn/rendering)
install(DIRECTORY shaders
	DESTINATION include/cgogn/rendering
	FILES_MATCHING PATTERN "*.h"
)

cgogn_create_package("${CMAKE_CURRENT_SOURCE_DIR}" "${CGOGN_SOURCE_DIR}" "include")
