#include <glad/glad.h> // Include glad first
#include <GLFW/glfw3.h> // Include GLFW after GLAD
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "ReadData.h"
#include "Display.h"
#include <stdio.h>
#include <iostream>





// Global font variables
ImFont* titleFont;  // Custom font for "Wallet"
ImFont* largeRomanFont;
ImFont* smallRomanFont;
ImFont* defaultFont; // Default font

// Function prototypes
void setupImGui(GLFWwindow* window);
void cleanupImGui();
void drawGrid(ImDrawList* drawList, ImVec2 windowSize, int gridHeight, int gridsPerRow, int startY);

const char *stockNames[20] = {"Microsoft", "Apple","Google", "Nvidia","Tesla", "Amazon", "Berkshire Hathaway", "Adobe","Costco","Mastercard",
                              "Coca-Cola", "Netflix", "Toyota", "Pepsico", "Mcdonald", "Shell", "Caterpillar", "Walt Disney", "Uber", "BHP Group"};

const char *stockCodes[20] = {"MSFT", "AAPL","GOOG", "NVDA","TSLA", "AMZA", "BRK-B", "ADBE","COST","MA",
                              "KO", "NFLX", "TM", "PEP", "MCD", "SHEL", "CAT", "DIS", "UBER", "BHP"};
                             
const char *stockFiles[20] = {"microsoft.csv", "apple.csv", "google.csv", "nvidia.csv", "tesla.csv", 
                             "amazon.csv", "berkshire.csv", "adobe.csv", "costco.csv", "mastercard.csv",
                             "coke.csv", "netflix.csv", "toyota.csv", "pepsico.csv", "mcdonald.csv",
                             "shell.csv", "caterpillar.csv", "disney.csv", "uber.csv", "bhp.csv"};


// Variable to track the current screen (0 for the default, 1 for a second screen, etc.)
int currentScreen = 0;
int selectedStockIndex = -1;






int main() {

    std::vector<Display> stockDisplays;


    // Initialize GLFW
if (!glfwInit()) {
    fprintf(stderr, "Failed to initialize GLFW\n");
    return -1;
} else {
    printf("GLFW initialized successfully.\n");
}


    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(800, 600, "Dear ImGui Test", NULL, NULL);
 if (!window) {
    fprintf(stderr, "Failed to create GLFW window\n");
    glfwTerminate();
    return -1;
} else {
    printf("GLFW window created successfully.\n");
}

    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD\n");
        return -1;
    }

    // Setup ImGui context
    setupImGui(window);

    for (int i = 0; i < 20; ++i) {
    stockDisplays.emplace_back(stockFiles[i]); // Pass stock code to Display constructor
    std::cout << "Initialized Display for stock: " << stockCodes[i] << std::endl;
}




    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents(); // Poll events

        // Start the ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Get window size for drawing grid
        ImVec2 windowSize = ImGui::GetIO().DisplaySize;

        ImGui::Begin("Portfolio", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse);
        // Set the background color to white
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)); // White color

        ImGui::SetWindowPos(ImVec2(0, 0)); // Set position to (0, 0)
        ImGui::SetWindowSize(ImVec2(800, 600)); // Set size to window size

        // Get the current draw list to draw the grid
         // Call drawGrid with grid height of 16 pixels, 3 grids per row, and starting at y = 100

        ImGui::SameLine();
        ImGui::SetCursorPos(ImVec2(50, 50));
        ImGui::Text("Mouse Position: (%.1f, %.1f)", ImGui::GetMousePos().x, ImGui::GetMousePos().y);
        ImVec2 cursorPos = ImGui::GetCursorPos();
        ImGui::Text("Cursor Position: (%.1f, %.1f)", cursorPos.x, cursorPos.y);

        // Display content based on the current screen
    if (currentScreen == 0) {
            // Main screen with stock list
 ImGui::PushFont(titleFont); // Set the custom font
            ImGui::SetCursorPos(ImVec2(350, 50));
            ImGui::Text("Wallet"); // This text uses the custom font
            ImGui::PopFont(); // Revert to the default font
            
            ImDrawList* drawList = ImGui::GetForegroundDrawList();
            drawGrid(drawList, windowSize, 50, 2, 100);
            for (int j=0; j<2; j++){
                for (int i=0; i<10; i++) {
                    ImGui::SetCursorPos(ImVec2((10 + 400*j),(105 + 50*i)));
                    ImGui::PushFont(largeRomanFont);
                    ImGui::Text("%s", stockNames[i + 10*j]);
                    ImGui::PopFont();
                    ImGui::SetCursorPos(ImVec2((10 + 400*j),(125 + 50*i)));
                    ImGui::PushFont(smallRomanFont);
                    ImGui::Text("%s", stockCodes[i + 10*j]);
                    ImGui::SetCursorPos(ImVec2((280 + 400*j),(110+ 50*i)));
                    ImGui::PopFont();

                    std::string buttonLabel = "View ##" + std::to_string(j) + "_" + std::to_string(i);
                    if (ImGui::Button(buttonLabel.c_str(), ImVec2(100, 30))) {
                    selectedStockIndex = (i + 10*j);
    std::cout << "Selected stock index: " << selectedStockIndex << std::endl;

                    currentScreen = 1; // Switch to screen 2
                    }                    
                    ImGui::SetCursorPos(ImVec2((700),(30)));


                }
            }
            if (ImGui::Button("Porfolio", ImVec2(100, 30))) {
                currentScreen = 2; // Switch to screen 2
            }

        
        }
        else if (currentScreen == 1 && selectedStockIndex != -1) {
    if (selectedStockIndex >= 0 && selectedStockIndex < stockDisplays.size()) {
        // Stock-specific screen for selected stock
     const Display& display = stockDisplays[selectedStockIndex];
        //const Display& display = "adobe.csv";
            ImGui::PushFont(titleFont);
            ImGui::SetCursorPos(ImVec2((350),(50)));
            ImGui::Text("%s", stockNames[selectedStockIndex]);
            ImGui::PopFont();
        
        ImGui::Text("Open Price: %s", display.single_open_prices(1).c_str());
        ImGui::Text("Close Price: %s", display.single_close_prices(1).c_str());
        ImGui::Text("Volume: %s", display.single_volumes(1).c_str());
        ImGui::Text("Date: %s", display.single_dates(1).c_str());
        ImGui::Text("Daily Change: %s", display.daily_change(1).c_str());
    } else {
        ImGui::Text("Invalid stock index.");
    }

    if (ImGui::Button("Go Back")) {
        currentScreen = 0;  // Return to main screen
        selectedStockIndex = -1; // Reset selected stock index
    }
        ImGui::SetCursorPos(ImVec2((340),(530)));
        if (ImGui::Button("Investment",  ImVec2(100, 40))) {
        currentScreen = 3;  
    }
    
}


        
        else if (currentScreen == 2) {
            ImGui::PushFont(titleFont); // Set the custom font
            ImGui::SetCursorPos(ImVec2(330, 50));
            ImGui::Text("Portfolio"); // This text uses the custom font
            ImGui::PopFont(); // Revert to the default font
            if (ImGui::Button("goback")) {
                currentScreen = 0; // Switch to screen 0 (original content)
            }
        }   
        else if (currentScreen == 3) {
            ImGui::PushFont(titleFont); 
            ImGui::SetCursorPos(ImVec2(330, 50));
            ImGui::Text("Investing"); 
            ImGui::PopFont(); 
            if (ImGui::Button("goback")) {
                currentScreen = 0; 
            }

        }

        ImGui::PopStyleColor(); // Pop the style color to revert to the previous color
        ImGui::End();

        // Render ImGui
        ImGui::Render();
        glClearColor(2.52f, 2.52f, 2.52f, 1.00f); // Background color
        glClear(GL_COLOR_BUFFER_BIT); // Clear the buffer
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); // Render ImGui

        glfwSwapBuffers(window); // Swap buffers
    
    }

    // Cleanup
    cleanupImGui();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

// Function to draw grid lines
void drawGrid(ImDrawList* drawList, ImVec2 windowSize, int gridHeight, int gridsPerRow, int startY) {
    ImU32 gridColor = IM_COL32(200, 200, 200, 255); // Light gray grid color

    float gridWidth = windowSize.x / gridsPerRow; // Width of each grid based on number of grids per row

    // Draw vertical lines (3 grids per row)
    for (int i = 0; i <= gridsPerRow; i++) {
        float x = i * gridWidth;
        drawList->AddLine(ImVec2(x, startY), ImVec2(x, windowSize.y), gridColor);
    }

    // Draw horizontal lines, starting at y = 100
    for (int y = startY; y < windowSize.y; y += gridHeight) {
        drawList->AddLine(ImVec2(0, y), ImVec2(windowSize.x, y), gridColor);
    }
}

void setupImGui(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io; // Setup io

    // Choose a style
    ImGui::StyleColorsLight(); // or ImGui::StyleColorsDark();

    // Load the default font (optional: can adjust size here if needed)
    defaultFont = io.Fonts->AddFontDefault(); // This sets the default font

    // Load the custom font
    titleFont = io.Fonts->AddFontFromFileTTF("Fonts/Vogue.ttf", 24.0f);
    largeRomanFont = io.Fonts->AddFontFromFileTTF("Fonts/timesnewroman.ttf", 20.0f);
    smallRomanFont = io.Fonts->AddFontFromFileTTF("Fonts/timesnewroman.ttf", 14.0f);
    if (titleFont == nullptr) {
        fprintf(stderr, "Could not load font file!\n");
    }

    // Optionally set global colors (affects all windows)
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)); // White color for all windows

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 120");
}

void cleanupImGui() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
 