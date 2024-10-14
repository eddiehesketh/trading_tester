test: all_unit_testing.cpp ReadData.cpp SetDeposit.cpp Dividend.cpp Display.cpp Investment.cpp Portfolio.cpp
	@echo "Compiling test program..."
	@g++ -std=c++11 all_unit_testing.cpp ReadData.cpp SetDeposit.cpp Dividend.cpp Portfolio.cpp Display.cpp Investment.cpp -o test
	@echo "Running test..."
	@./test

run_program: ImGUITest.cpp Display.cpp ReadData.cpp Investment.cpp Dividend.cpp libs/glad/src/glad.c \
	imgui/imgui.cpp imgui/imgui_draw.cpp imgui/imgui_widgets.cpp imgui/imgui_tables.cpp \
	imgui/backends/imgui_impl_glfw.cpp imgui/backends/imgui_impl_opengl3.cpp
	@echo "Compiling imgui_test program..."
	@g++ -o imgui_test ImGUITest.cpp Display.cpp ReadData.cpp Investment.cpp Dividend.cpp libs/glad/src/glad.c \
		imgui/imgui.cpp imgui/imgui_draw.cpp imgui/imgui_widgets.cpp imgui/imgui_tables.cpp \
		imgui/backends/imgui_impl_glfw.cpp imgui/backends/imgui_impl_opengl3.cpp \
		-Ilibs/glad/include -I/opt/homebrew/include -Iimgui -Iimgui/backends \
		-L/opt/homebrew/lib -lglfw -framework OpenGL -DIMGUI_IMPL_OPENGL_LOADER_GLAD -std=c++14
	@echo "Running imgui_test..."
	@./imgui_test

clean:
	@echo "Cleaning up..."
	@rm -f test imgui_test

# Target to build everything
all: test imgui_test