#include <glad/glad.h> // Include glad first
#include <GLFW/glfw3.h> // Include GLFW after GLAD
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "ReadData.h"
#include "Display.h"
#include <stdio.h>
#include <iostream>
#include <algorithm>





// Global font variables
ImFont* titleFont;  // Custom font for "Wallet"
ImFont* largeRomanFont;
ImFont* smallRomanFont;
ImFont* defaultFont; // Default font

// Function prototypes
void setupImGui(GLFWwindow* window);
void cleanupImGui();
void drawGrid(ImDrawList* drawList, ImVec2 windowSize, int gridHeight, int gridsPerRow, int startY);

const char *stockNames[20] = {"Microsoft", "Apple","Google", "Nvidia","Tesla", "Amazon", "Berkshire", "Adobe","Costco","Mastercard",
                              "Coca-Cola", "Netflix", "Toyota", "Pepsico", "Mcdonald", "Shell", "Caterpillar", "Walt Disney", "Uber", "BHP Group"};

const char *stockCodes[20] = {"MSFT", "AAPL","GOOG", "NVDA","TSLA", "AMZA", "BRK-B", "ADBE","COST","MA",
                              "KO", "NFLX", "TM", "PEP", "MCD", "SHEL", "CAT", "DIS", "UBER", "BHP"};
                             
const char *stockFiles[20] = {"microsoft.csv", "apple.csv", "google.csv", "nvidia.csv", "tesla.csv", 
                             "amazon.csv", "berkshire.csv", "adobe.csv", "costco.csv", "mastercard.csv",
                             "coke.csv", "netflix.csv", "toyota.csv", "pepsico.csv", "mcdonald.csv",
                             "shell.csv", "caterpillar.csv", "disney.csv", "uber.csv", "bhp.csv"};

enum class TimeRange { Max, Year1, Month6, Month1 };
TimeRange selectedRange = TimeRange::Max;

// Variable to track the current screen (0 for the default, 1 for a second screen, etc.)
int currentScreen = 0;
int selectedStockIndex = -1;






int main() {

    std::vector<Display> stockDisplays;
// Test Graph

    // Initialize GLFW
if (!glfwInit()) {
    fprintf(stderr, "Failed to initialize GLFW\n");
    return -1;
} else {
    printf("GLFW initialized successfully.\n");
}


    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(800, 600, "Stock Simulator", NULL, NULL);
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

        ImGui::Begin("Stock Simulator", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse);
        // Set the background color to white
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)); // White color

        ImGui::SetWindowPos(ImVec2(0, 0)); // Set position to (0, 0)
        ImGui::SetWindowSize(ImVec2(800, 600)); // Set size to window size



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
                    const Display& displayScreen0 = stockDisplays[i + 10 * j];

                    // Call daily_change and check for NULL directly
                    std::string dailyChangeStr = displayScreen0.daily_change(1).c_str();


                    ImGui::SetCursorPos(ImVec2((10 + 400*j),(105 + 50*i)));
                    ImGui::PushFont(largeRomanFont);
                    ImGui::Text("%s", stockNames[i + 10*j]);
                    ImGui::PopFont();
                    ImGui::SetCursorPos(ImVec2((10 + 400*j),(125 + 50*i)));
                    ImGui::PushFont(smallRomanFont);
                    ImGui::Text("%s", stockCodes[i + 10*j]);

                    ImGui::SetCursorPos(ImVec2((120 + 400 * j), (115 + 50 * i)));

                    // Check if daily change has enough elements before accessing
                    if (dailyChangeStr != "N/A" && !dailyChangeStr.empty()) {
                        ImGui::SetCursorPos(ImVec2((120 + 400 * j), (115 + 50 * i)));
                    if (dailyChangeStr[0] == '-') {
                         ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 0, 0, 255)); // Green for positive change
                        } else {
                        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 0, 255)); // Red for negative change
                     }
                        ImGui::Text("%s%%", dailyChangeStr.c_str());  // Display the second element, if available
                        ImGui::PopStyleColor();
                    } else {
                        ImGui::SetCursorPos(ImVec2((120 + 400 * j), (115 + 50 * i)));
                        ImGui::Text("Daily Change: N/A");  // Display fallback if data is missing
                    }
                    ImGui::SetCursorPos(ImVec2((280 + 400*j),(110 + 50*i)));
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
    
    ImVec2 windowSize = ImGui::GetWindowSize();
    // Calculate text width based on the selected font and stock name text
    ImGui::PushFont(titleFont);
    ImVec2 textSize = ImGui::CalcTextSize(stockNames[selectedStockIndex]);
    // Calculate position to center the text
    ImVec2 centeredPos((windowSize.x - textSize.x) / 2.0f, (50));
    ImGui::SetCursorPos(centeredPos);
    // Display the centered text
    ImGui::Text("%s", stockNames[selectedStockIndex]);
    ImGui::PopFont();

    

        

// Retrieve open prices for plotting
    const std::vector<float>& openPrices = display.get_open_prices();
    const std::vector<float>& closePrices = display.get_close_prices();
    const std::vector<long long>& volume = display.get_volume();
    const std::vector<std::string>& dates = display.get_dates();


    ImGui::SetCursorPos(ImVec2(100, 75));
    ImGui::PushItemWidth(150.0f);

    const char* timeRangeLabels[] = { "Max", "1 Year", "6 Month", "1 Month" };
    int currentRangeIndex = static_cast<int>(selectedRange);
    if (ImGui::Combo("Time Range", &currentRangeIndex, timeRangeLabels, IM_ARRAYSIZE(timeRangeLabels))) {
            selectedRange = static_cast<TimeRange>(currentRangeIndex);
    }

ImGui::PopItemWidth();
// Filter data based on selected time range
    std::vector<float> filteredOpenPrices;
    std::vector<float> filteredClosePrices;
    std::vector<float> filteredVolume;
    std::vector<std::string> filteredDates;
    

    size_t dataSize = openPrices.size();
    size_t startIndex = 0;

    switch (selectedRange) {
        case TimeRange::Max:
            startIndex = 0;
            break;
        case TimeRange::Year1:
            startIndex = (dataSize > 252) ? dataSize - 252 : 0;  // Approx. 252 trading days in a year
            break;
        case TimeRange::Month6:
            startIndex = (dataSize > 126) ? dataSize - 126 : 0;   
            break;
        case TimeRange::Month1:
            startIndex = (dataSize > 21) ? dataSize - 21 : 0;   
            break;
    }
    filteredOpenPrices.assign(openPrices.begin() + startIndex, openPrices.end());
    filteredClosePrices.assign(closePrices.begin() + startIndex, closePrices.end());
    filteredVolume.assign(volume.begin() + startIndex, volume.end());
    filteredDates.assign(dates.begin() + startIndex, dates.end());

if (!filteredOpenPrices.empty()) {
                    float graphWidth = 600.0f;  // Set desired width for the graph box
                    float graphHeight = 200.0f; // Set desired height for the graph box
                    ImVec2 graphPos((windowSize.x - graphWidth) / 2, 100.0f);  // Centered horizontally, offset from top
                    ImGui::SetCursorPos(graphPos);

                    ImGui::BeginChild("GraphWindow", ImVec2(graphWidth, graphHeight), true, ImGuiWindowFlags_HorizontalScrollbar);
                    ImGui::PlotLines("##OpenPrices", filteredOpenPrices.data(), filteredOpenPrices.size(), 0, nullptr, FLT_MIN, FLT_MAX, ImVec2(graphWidth - 20, 150));


                    
                    static int hoveredIndex = -1;
                    
                    float plotWidth = ImGui::GetItemRectSize().x;
                    if (ImGui::IsItemHovered()) {
                        
                        ImVec2 mousePosInGraph = ImGui::GetMousePos();
                        ImVec2 graphOrigin = ImGui::GetItemRectMin();  // Top-left of PlotLines area

                         float relativeX = mousePosInGraph.x - graphOrigin.x;
                         hoveredIndex = static_cast<int>((relativeX / plotWidth) * filteredOpenPrices.size());
                            // Calculate the x-position of the line to follow the mouse
                        float lineX = mousePosInGraph.x;
                        // Clamp to valid range
                        hoveredIndex = std::max(0, std::min(hoveredIndex, static_cast<int>(filteredOpenPrices.size() - 1)));

                        ImGui::SetTooltip("Open Price: $%.2f\nClose Price: $%.2f\nVolume: $%.0f", 
                        filteredOpenPrices[hoveredIndex], filteredClosePrices[hoveredIndex], filteredVolume[hoveredIndex]);
                        
                        
                      
                        ImDrawList* drawList = ImGui::GetWindowDrawList();
                        ImVec2 graphTop = ImGui::GetItemRectMin();  // Top of the graph box
                        ImVec2 graphBottom = ImGui::GetItemRectMax();  // Bottom of the graph box
                        drawList->AddLine(ImVec2(lineX, 100), ImVec2(lineX, graphBottom.y + 100), IM_COL32(200, 0, 0, 255), 1.5f);

                    }
                    
                    // Draw the hover line based on the corrected hoveredIndex position
                    float price = filteredOpenPrices[hoveredIndex];
                    const std::string& dateLabel = filteredDates[hoveredIndex];
                    ImVec2 lineStartPos = ImVec2(graphPos.x + (plotWidth * hoveredIndex / filteredOpenPrices.size()), graphPos.y);
                    ImGui::EndChild();

    if (hoveredIndex >= 0 && hoveredIndex < filteredOpenPrices.size()) {
        

         ImGui::SetCursorPosY(graphPos.y + graphHeight + 20);  // Position date label below the graph
         ImGui::SetCursorPosX(lineStartPos.x - 20);  // Adjust for label alignment
         ImGui::Text("%s", dateLabel.c_str());
    }
                    

                } else {
                    ImGui::Text("No data available for plotting.");
                }

    } else {
        ImGui::Text("Invalid stock index.");
    }

        ImGui::SetCursorPos(ImVec2((5),(575)));
        if (ImGui::Button("Go Back")) {
            currentScreen = 0; // Switch to screen 0 (original content)
            selectedStockIndex = -1;
        }
        ImGui::SetCursorPos(ImVec2((340),(530)));
        if (ImGui::Button("Investment",  ImVec2(100, 40))) {
        currentScreen = 3;  
    }
    
}       
        else if (currentScreen == 2) {
            ImGui::PushFont(titleFont); // Set the custom font
            ImGui::SetCursorPos(ImVec2(320, 50));
            ImGui::Text("Portfolio"); // This text uses the custom font
            ImGui::PopFont(); // Revert to the default font

            ImGui::SetCursorPos(ImVec2((5),(575)));
            if (ImGui::Button("Go Back")) {
                currentScreen = 0; // Switch to screen 0 (original content)
            }
        }   
        else if (currentScreen == 3) {
            ImGui::PushFont(titleFont); 
            ImGui::SetCursorPos(ImVec2(330, 50));
            ImGui::Text("Investing"); 
            ImGui::PopFont(); 

            int investmentIndex = -1;

            ImGui::SetCursorPos(ImVec2((30),(150)));
            if (ImGui::Button("Dividend",  ImVec2(100, 40))) {
            currentScreen = 4;  
            investmentIndex = 1;
            }
            ImGui::SetCursorPos(ImVec2((30 + (windowSize.x / 4)),(150)));
            if (ImGui::Button("MeanReversion",  ImVec2(100, 40))) {
            currentScreen = 4;  
            investmentIndex = 2;
            }
            ImGui::SetCursorPos(ImVec2((30 + (windowSize.x * 2 / 4)),(150)));
            if (ImGui::Button("SetDeposit",  ImVec2(100, 40))) {
            currentScreen = 4;  
            investmentIndex = 3;
            }
            ImGui::SetCursorPos(ImVec2((30 + (windowSize.x * 3 / 4)),(150)));
            if (ImGui::Button("MovingAverageCrossover",  ImVec2(100, 40))) {
            currentScreen = 4;  
            investmentIndex = 4;
            }


            ImGui::SetCursorPos(ImVec2((5),(575)));
            if (ImGui::Button("Go Back")) {
                currentScreen = 1; 
            }

        }
        else if (currentScreen == 4) {
            ImGui::PushFont(titleFont); 
            ImGui::SetCursorPos(ImVec2(330, 50));
            ImGui::Text("Investing"); 
            ImGui::PopFont(); 


            ImGui::SetCursorPos(ImVec2((340),(530)));
            if (ImGui::Button("Investment",  ImVec2(100, 40))) {
            currentScreen = 4;  
            }



            ImGui::SetCursorPos(ImVec2((5),(575)));
            if (ImGui::Button("Go Back")) {
                currentScreen = 3; 
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
 