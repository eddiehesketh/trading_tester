#include <glad/glad.h> // Include glad first
#include <GLFW/glfw3.h> // Include GLFW after GLAD
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "ReadData.h"
#include "Display.h"
#include "Dividend.h"
#include "Momentum.h"
#include "RiskAssesment.h"
#include "SetDeposit.h"
#include "MovingAverageCrossover.h"
#include "Portfolio.h"
#include "Investment.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>




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
                             "coke.csv", "netflix.csv", "toyota.csv", "pepsi.csv", "mcdonalds.csv",
                             "shell.csv", "caterpillar.csv", "disney.csv", "uber.csv", "bhp.csv"};

const char *investmentNames[4] = {"Dividend", "Momentum", "Set Deposit", "Moving Average Crossover"};

enum class TimeRange { Max, Year1, Month6, Month1 };
TimeRange selectedRange = TimeRange::Max;

// Variable to track the current screen (0 for the default, 1 for a second screen, etc.)
int currentScreen = 0;
int selectedStockIndex = -1;
int investmentIndex = -1;
static bool showFinalCapitalPopup = false;
static float finalCapital = 0.0f;
static bool showConfirmResetPopup = false;
static int earliestYear;



int main() {

std::vector<std::unique_ptr<Display>> stockDisplays;
Portfolio portfolio;

float bank = 100000.0f;

for (int i = 0; i < 20; ++i) {
stockDisplays.emplace_back(std::make_unique<Display>(std::string(stockFiles[i])));
}




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

        // Display content based on the current screen
    if (currentScreen == 0) {
            // Main screen with stock list
 ImGui::PushFont(titleFont); // Set the custom font
            ImGui::SetCursorPos(ImVec2(350, 50));
            ImGui::Text("Wallet"); // This text uses the custom font
            ImGui::SetCursorPos(ImVec2(10, 40));
            ImGui::Text("Bank: $%.2f", bank); // This text uses the custom font
            ImGui::PopFont(); // Revert to the default font

            ImDrawList* drawList = ImGui::GetForegroundDrawList();
            drawGrid(drawList, windowSize, 50, 2, 100);


            for (int j=0; j<2; j++){
                for (int i=0; i<10; i++) {
                    const Display& displayScreen0 = *(stockDisplays[i + 10 * j]);

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
                        ImGui::Text("%s", dailyChangeStr.c_str());  // Display the second element, if available
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



                }
            }
            ImGui::SetCursorPos(ImVec2((680),(30)));
            if (ImGui::Button("Portfolio", ImVec2(100, 30))) {
                currentScreen = 2; // Switch to screen 2
            }

        
        }
        else if (currentScreen == 1 && selectedStockIndex != -1) {
    if (selectedStockIndex >= 0 && selectedStockIndex < stockDisplays.size()) {

        // Stock-specific screen for selected stock
        const Display& display = *(stockDisplays[selectedStockIndex]);
         // Retrieve price data
        const std::vector<float>& openPrices = display.get_open_prices();
        const std::vector<float>& closePrices = display.get_close_prices();
        const std::vector<float>& highPrices = display.get_stock_high();
        const std::vector<float>& lowPrices = display.get_stock_low();
        const std::vector<long long>& volume = display.get_volume();
        const std::vector<std::string>& dates = display.get_dates();

    float currentClosePrice = closePrices.back();
    ImVec2 windowSize = ImGui::GetWindowSize();



    // Calculate text width based on the selected font and stock name text
    ImGui::PushFont(titleFont);

    // Calculate the size of the full text
    ImVec2 textSize = ImGui::CalcTextSize(stockNames[selectedStockIndex]);
    // Calculate position to center the text
    ImGui::SetCursorPos(ImVec2((windowSize.x - textSize.x) / 2.0f, (40)));
    // Display the centered text
    ImGui::Text("%s", stockNames[selectedStockIndex]);
    ImGui::PopFont();

       ImGui::PushFont(largeRomanFont);
    std::string fullText = std::string("Current price - $") + std::to_string(currentClosePrice);
    ImVec2 floatSize = ImGui::CalcTextSize(fullText.c_str());
    ImGui::SetCursorPos(ImVec2(((windowSize.x - floatSize.x) / 2.0f) + 20 , 65));
    ImGui::Text("Current price - $%.2f", currentClosePrice);
    ImGui::PopFont();



        // Find the minimum year in the dates
        earliestYear = 2025; // default latest year in your code
        for (const auto& date : dates) {
            int year = std::stoi(date.substr(date.size() - 4)); // Extract year from date string (assuming "dd/mm/yyyy" format)
            earliestYear = std::min(earliestYear, year);
        }


        // Show last 7 days' data
        size_t numDays = 7;
        size_t startIdx = openPrices.size() >= numDays ? openPrices.size() - numDays : 0;
        ImGui::PushFont(largeRomanFont);
        ImVec2 textSize2 = ImGui::CalcTextSize("Data Over The Last 7 Days");
        // Calculate position to center the text
        ImVec2 centeredPos2((windowSize.x - textSize2.x) / 2.0f, (340));
        ImGui::SetCursorPos(centeredPos2);
        // Display the centered text
        ImGui::Text("Data Over The Last 7 Days");
        ImGui::PopFont();
        // Create the table
        ImGui::SetCursorPos(ImVec2(80, 370)); // Adjust position as needed
        if (ImGui::BeginTable("StockDataTable", 6, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
            ImGui::TableSetupColumn("Date");
            ImGui::TableSetupColumn("Open ($)");
            ImGui::TableSetupColumn("Close ($)");
            ImGui::TableSetupColumn("High ($)");
            ImGui::TableSetupColumn("Low ($)");
            ImGui::TableSetupColumn("Volume ($)");
            ImGui::TableHeadersRow();

            for (size_t i = startIdx; i < openPrices.size(); ++i) {
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0); ImGui::Text("%s", dates[i].c_str());
                ImGui::TableSetColumnIndex(1); ImGui::Text("%.2f", openPrices[i]);
                ImGui::TableSetColumnIndex(2); ImGui::Text("%.2f", closePrices[i]);
                ImGui::TableSetColumnIndex(3); ImGui::Text("%.2f", highPrices[i]);
                ImGui::TableSetColumnIndex(4); ImGui::Text("%.2f", lowPrices[i]);
                ImGui::TableSetColumnIndex(5); ImGui::Text("%lld", volume[i]);
            }
            ImGui::EndTable();
        }

    


    ImGui::SetCursorPos(ImVec2(100, 75));
    ImGui::PushItemWidth(150.0f);

    const char* timeRangeLabels[] = { "Max", "1 Year", "6 Month", "1 Month" };
    int currentRangeIndex = static_cast<int>(selectedRange);
    if (ImGui::Combo(" ", &currentRangeIndex, timeRangeLabels, IM_ARRAYSIZE(timeRangeLabels))) {
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
 ImGui::PushFont(titleFont);
    ImGui::SetCursorPos(ImVec2(320, 50));
    ImGui::Text("Portfolio");
    ImGui::PopFont();



    // Display each investment in the portfolio
    for (int i = 0; i < portfolio.get_count(); ++i) {
        Investment* inv = portfolio.get_investment(i);
        ImGui::Separator();

        // Show each investment's details
        ImGui::Text("Investment %d: %s", i + 1, inv->get_investment_type().c_str());
        ImGui::Text("  Company: %s", inv->get_name().c_str());
        ImGui::Text("  Start Date: %s", inv->get_start_date().c_str());
        ImGui::Text("  Initial Capital: $%.2f", inv->get_capital());
        ImGui::Text("  Final Capital: $%.2f", inv->get_final_capital());
        ImGui::Text("  Profit: $%.2f", inv->get_profits());

        // Risk assessment for the investment
        RiskAssesment riskAssessment(inv); // Create RiskAssesment object for the current investment
        std::string riskRating = riskAssessment.get_risk_rating();
        ImGui::Text("  Risk Rating: %s", riskRating.c_str());


        // Add a "Remove" button for this investment
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5); // Small space above the button
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 680); // Align button to the right
        if (ImGui::Button(("Remove##" + std::to_string(i)).c_str(), ImVec2(100, 30))) {
            bank -= inv->get_profits(); // Optionally, add back the capital to the bank
            portfolio.remove_investment(i); // Remove investment at index i
        }


        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10); // Add some spacing between investments
    }


        // Calculate Y position dynamically
    float currentY = ImGui::GetCursorPosY(); // Get the current Y position

    // Add some space before the buttons and summary
    ImGui::SetCursorPosY(currentY + 20);


    ImGui::Separator();
    ImGui::Text("Total Portfolio Profit: $%.2f", portfolio.get_portfolio_value());
    ImGui::Text("Bank Balance: $%.2f", bank);
    ImGui::Separator();

        // Button to export portfolio to a summary file
    ImGui::SetCursorPosX(225);
    if (ImGui::Button("Export Portfolio", ImVec2(150, 40))) {
        portfolio.write_portfolio_summary();
        ImGui::OpenPopup("ExportConfirmation");
    }
    ImGui::SameLine();
    ImGui::SetCursorPosX(425);
    if (ImGui::Button("Reset Portfolio", ImVec2(150, 40))) {
         showConfirmResetPopup = true;
    }

        // Confirmation popup
        ImGui::Separator();
    if (ImGui::BeginPopupModal("ExportConfirmation", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("Portfolio summary exported to 'investment_summary.txt'.");
        if (ImGui::Button("OK", ImVec2(120, 0))) {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }


// Confirm Reset Popup Modal
    if (showConfirmResetPopup) {
        ImGui::OpenPopup("Confirm Reset");
    }
    if (ImGui::BeginPopupModal("Confirm Reset", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("Are you sure you want to reset the portfolio?");
        ImGui::Separator();

        if (ImGui::Button("Yes", ImVec2(120, 0))) {
            // Reset portfolio investments and bank balance
            while (portfolio.get_count() > 0) {
                portfolio.remove_investment(0); // Remove each investment one by one
            }
            bank = 100000.0f; // Reset bank to initial value

            showConfirmResetPopup = false; // Close popup
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("No", ImVec2(120, 0))) {
            showConfirmResetPopup = false; // Close popup without action
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    ImGui::SetCursorPos(ImVec2((5), (30)));
    if (ImGui::Button("Go Back")) {
        currentScreen = 0;
    }
}   
        else if (currentScreen == 3) {
    ImGui::PushFont(titleFont); 
    ImGui::SetCursorPos(ImVec2(330, 30));
    ImGui::Text("Investing"); 
    ImGui::PopFont(); 

    ImGui::SetCursorPos(ImVec2((5),(575)));
     if (ImGui::Button("Go Back")) {
        currentScreen = 1; 
    }

    ImGui::PushFont(titleFont);
    ImGui::SetCursorPos(ImVec2(15,30));
    ImGui::Text("%s", stockNames[selectedStockIndex]);
    ImGui::PopFont();

    // Create a padding style
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 10));
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.95f, 0.95f, 0.95f, 1.0f)); // Light background for child windows

    // Investment Option: Dividend
    ImGui::SetCursorPos(ImVec2(30, 80));
    ImGui::BeginChild("DividendChild", ImVec2(700, 90), true, ImGuiWindowFlags_NoScrollbar);
    ImGui::SetCursorPosX(20);  // Add padding on the left
    ImGui::SetCursorPosY(25);
    if (ImGui::Button("Dividend", ImVec2(100, 40))) {
        currentScreen = 4;  
        investmentIndex = 0;
    }
    ImGui::SameLine();
    ImGui::SetCursorPosX(140);
    ImGui::TextWrapped("Dividend provides steady returns by reinvesting dividends from selected stocks, suitable for low-risk, income-focused investors.");
    ImGui::EndChild();

    // Investment Option: Momentum
    ImGui::SetCursorPos(ImVec2(30, 190));
    ImGui::BeginChild("MomentumChild", ImVec2(700, 90), true, ImGuiWindowFlags_NoScrollbar);
    ImGui::SetCursorPosX(20); 
    ImGui::SetCursorPosY(25);
    if (ImGui::Button("Momentum", ImVec2(100, 40))) {
        currentScreen = 4;  
        investmentIndex = 1;
    }
    ImGui::SameLine();
    ImGui::SetCursorPosX(140);
    ImGui::TextWrapped("Momentum is a high-risk strategy that seeks to profit from stocks showing strong upward trends in the short term.");
    ImGui::EndChild();

    // Investment Option: Set Deposit
    ImGui::SetCursorPos(ImVec2(30, 300));
    ImGui::BeginChild("SetDepositChild", ImVec2(700, 90), true, ImGuiWindowFlags_NoScrollbar);
    ImGui::SetCursorPosX(20); 
    ImGui::SetCursorPosY(25);
    if (ImGui::Button("SetDeposit", ImVec2(100, 40))) {
        currentScreen = 4;  
        investmentIndex = 2;
    }
    ImGui::SameLine();
    ImGui::SetCursorPosX(140);
    ImGui::TextWrapped("Set Deposit is a low to medium-risk investment where a fixed amount is deposited at regular intervals to accumulate over time.");
    ImGui::EndChild();

    // Investment Option: Moving Average Crossover
    ImGui::SetCursorPos(ImVec2(30, 410));
    ImGui::BeginChild("MovingAverageCrossoverChild", ImVec2(700, 90), true, ImGuiWindowFlags_NoScrollbar);
    ImGui::SetCursorPosX(20); 
    ImGui::SetCursorPosY(25);
    if (ImGui::Button("MAC", ImVec2(100, 40))) {
        currentScreen = 4;  
        investmentIndex = 3;
    }
    ImGui::SameLine();
    ImGui::SetCursorPosX(140);
    ImGui::TextWrapped("Moving Average Crossover (MAC), is a technical, high-risk strategy that buys and sells based on short-term and long-term moving average crossovers to capture trends.");
    ImGui::EndChild();


    // Pop style variables and colors to return to defaults
    ImGui::PopStyleColor();
    ImGui::PopStyleVar();
}

        else if (currentScreen == 4 && investmentIndex != -1) {

            

            
const char* payFreqOptions[] = { "Monthly", "Quarterly" };
static int payFreqIndex = 0;
static bool reinvestStatus = true;  // Static to persist across frames
static float capitalInvestment = 0.0f;
static int period = 1;
static int secondPeriod = 1;
float capitalProfit = finalCapital - capitalInvestment;
static bool insufficientFunds = false;
static bool invalidPeriod1 = false;
static bool invalidPeriod2 = false;
static bool invalidInput = false;
static bool invalidDate = false;
static bool recentDate = false;
std::string availableStartDate;
static Investment* newInvestment = nullptr;

            ImGui::PushFont(titleFont); 
            ImVec2 textSize = ImGui::CalcTextSize(investmentNames[investmentIndex]);
            ImVec2 centeredPos((windowSize.x - textSize.x) / 2.0f, (50));
            ImGui::SetCursorPos(centeredPos);
            ImGui::Text("%s", investmentNames[investmentIndex]); 
            ImGui::PopFont(); 

                ImGui::PushFont(titleFont);
                ImGui::SetCursorPos(ImVec2(15,30));
                ImGui::Text("%s", stockNames[selectedStockIndex]);
                ImGui::PopFont();

            // Styling for input box
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 5));  // Add padding inside input box
        ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(240, 240, 255, 255));  // Light background color
        ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, IM_COL32(200, 200, 250, 255));  // Darker on hover
        ImGui::PushStyleColor(ImGuiCol_FrameBgActive, IM_COL32(180, 180, 230, 255));  // Darker on active
        ImGui::PushStyleColor(ImGuiCol_Border, IM_COL32(100, 100, 200, 255));  // Blue border color
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.0f);  // Rounded corners
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.5f);  // Border size

       // Center the label above the input box
ImVec2 labelPos((windowSize.x - 165.0f) / 2.0f, 100.0f);
ImGui::SetCursorPos(labelPos);
ImGui::Text("Enter Capital to Invest:");

// Center the input box
ImGui::SetCursorPos(ImVec2((windowSize.x - 150.0f) / 2.0f, 130.0f));
ImGui::SetNextItemWidth(150.0f);
ImGui::InputFloat("##CapitalInput", &capitalInvestment, 0.0f, 0.0f, "%.2f", ImGuiInputTextFlags_AutoSelectAll);

if (capitalInvestment > bank){
    ImGui::SetCursorPos(ImVec2((windowSize.x - 125.0f) / 2.0f, 530.0f)); 
    ImGui::Text("Insufficient funds");
    insufficientFunds = true;
} else {
    insufficientFunds = false;
}
if(capitalInvestment < 0){
    ImGui::SetCursorPos(ImVec2((windowSize.x - 200.0f) / 2.0f, 530.0f)); 
    ImGui::Text("Invalid input, please try again");
    invalidInput = true;
} else {
    invalidInput = false;
}



if (investmentIndex == 0){
// Pay Frequency Selector
    ImGui::SetCursorPos(ImVec2((windowSize.x - 150.0f) / 2.0f, 240.0f));
    ImGui::Text("Select Payment Frequency:");

    ImGui::SetCursorPos(ImVec2((windowSize.x - 150.0f) / 2.0f, 270.0f));
    ImGui::SetNextItemWidth(150.0f);
    if (ImGui::BeginCombo("##PayFrequency", payFreqOptions[payFreqIndex])) {
        for (int n = 0; n < IM_ARRAYSIZE(payFreqOptions); n++) {
            bool isSelected = (payFreqIndex == n);
            if (ImGui::Selectable(payFreqOptions[n], isSelected))
                payFreqIndex = n;
            if (isSelected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }


    // Reinvest Status Checkbox
    ImGui::SetCursorPos(ImVec2((windowSize.x - 150.0f) / 2.0f, 310.0f));
    ImGui::Text("Reinvest Dividends:");
    ImGui::SetCursorPos(ImVec2((windowSize.x - 150.0f) / 2.0f, 340.0f));
    ImGui::Checkbox("##ReinvestStatus", &reinvestStatus);
} else if (investmentIndex == 1){
            // Period Selector (for Momentum)
        ImGui::SetCursorPos(ImVec2((windowSize.x - 160.0f) / 2.0f, 240.0f));
        ImGui::Text("Select Momentum Period:");
        ImGui::SetCursorPos(ImVec2((windowSize.x - 150.0f) / 2.0f, 270.0f));
        ImGui::SetNextItemWidth(150.0f);
        ImGui::InputInt("##PeriodInput", &period);

        if(period < 0){
        ImGui::SetCursorPos(ImVec2((windowSize.x - 200.0f) / 2.0f, 550.0f)); 
        ImGui::Text("Invalid period, please try again");
        invalidPeriod1 = true;
    } else {
        invalidPeriod1 = false;
    }
}
if (investmentIndex == 3) {
       
            // Period Selector (for MAC)
        ImGui::SetCursorPos(ImVec2((windowSize.x - 190.0f) / 2.0f, 240.0f));
        ImGui::Text("Select Moving Average Period 1:");
        ImGui::SetCursorPos(ImVec2((windowSize.x - 150.0f) / 2.0f, 270.0f));
        ImGui::SetNextItemWidth(150.0f);
        ImGui::InputInt("##PeriodInput", &period);

        if(period < 0){
        ImGui::SetCursorPos(ImVec2((windowSize.x - 200.0f) / 2.0f, 550.0f)); 
        ImGui::Text("Invalid period, please try again");
        invalidPeriod1 = true;
    } else {
        invalidPeriod1 = false;
    }

        ImGui::SetCursorPos(ImVec2((windowSize.x - 190.0f) / 2.0f, 310.0f));
        ImGui::Text("Select Moving Average Period 2:");
        ImGui::SetCursorPos(ImVec2((windowSize.x - 150.0f) / 2.0f, 340.0f));
        ImGui::SetNextItemWidth(150.0f);
        ImGui::InputInt("##secondPeriodInput", &secondPeriod);
        if(secondPeriod < 0){
        ImGui::SetCursorPos(ImVec2((windowSize.x - 200.0f) / 2.0f, 570.0f)); 
        ImGui::Text("Invalid period, please try again");
        invalidPeriod2 = true;
    } else {
        invalidPeriod2 = false;
    }




}


ImVec2 dateTextPos((windowSize.x - 150.0f) / 2.0f, 170.0f);
ImGui::SetCursorPos(dateTextPos);
ImGui::Text("Select Start Date:");

static int day = 1, month = 1, year = 2024;

// Position date pickers in the center
ImVec2 datePos((windowSize.x - 250.0f) / 2.0f, 190.0f);
ImGui::SetCursorPos(datePos);

// Day Picker
ImGui::PushItemWidth(60);
if (ImGui::BeginCombo("##Day", std::to_string(day).c_str())) {
    for (int i = 1; i <= 31; ++i) {
        bool isSelected = (day == i);
        if (ImGui::Selectable(std::to_string(i).c_str(), isSelected)) {
            day = i;
        }
        if (isSelected) ImGui::SetItemDefaultFocus();
    }
    ImGui::EndCombo();
}
ImGui::PopItemWidth();
ImGui::SameLine();

// Month Picker
ImGui::PushItemWidth(100);
const char* months[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
if (ImGui::BeginCombo("##Month", months[month - 1])) {
    for (int i = 1; i <= 12; ++i) {
        bool isSelected = (month == i);
        if (ImGui::Selectable(months[i - 1], isSelected)) {
            month = i;
        }
        if (isSelected) ImGui::SetItemDefaultFocus();
    }
    ImGui::EndCombo();
}
ImGui::PopItemWidth();
ImGui::SameLine();

// Year Picker
ImGui::PushItemWidth(80);
if (ImGui::BeginCombo("##Year", std::to_string(year).c_str())) {
    for (int i = earliestYear+1; i <= 2024; ++i) {
        bool isSelected = (year == i);
        if (ImGui::Selectable(std::to_string(i).c_str(), isSelected)) {
            year = i;
        }
        if (isSelected) ImGui::SetItemDefaultFocus();
    }
    ImGui::EndCombo();
}
ImGui::PopItemWidth();


if (((month == 4 || month == 6 || month == 9 || month == 11) && (day > 30)) || ((month == 2) && (day > 28))){
    ImGui::SetCursorPos(ImVec2((windowSize.x - 200.0f) / 2.0f, 490.0f)); 
    ImGui::Text("Invalid date, please try again");
    invalidDate = true;
} else {
    invalidDate = false;
}

if (((year == 2024) && (month > 6)) || ((month == 6) && (day > 10))){
    ImGui::SetCursorPos(ImVec2((windowSize.x - 200.0f) / 2.0f, 490.0f)); 
    ImGui::Text("Date is too recent");
    recentDate = true;
} else {
    recentDate = false;

}

std::string startDate = std::to_string(day) + "/" + std::to_string(month) + "/" + std::to_string(year);





// Handle Invest button
if (!insufficientFunds && !invalidInput && !invalidPeriod1 && !invalidPeriod2 && !invalidDate && !recentDate) {
ImGui::SetCursorPos(ImVec2((windowSize.x - 100.0f) / 2.0f, 530.0f));
if (ImGui::Button("Invest", ImVec2(100, 40))) {

            newInvestment = nullptr;    

            std::cout<<startDate<<std::endl;
            // Create Dividend instance with user input
            bool showFinalCapital = true;

        ReadData readData(stockFiles[selectedStockIndex]);

if (investmentIndex == 0){
    std::cout << "Start Date: " << startDate << ", Capital: " << capitalInvestment << ", Pay Frequency: " << payFreqOptions[payFreqIndex] << "Stock Selected: " << stockFiles[selectedStockIndex] << "Reinvest Status: " << reinvestStatus <<  "\n";
  newInvestment = new Dividend(startDate, capitalInvestment, payFreqOptions[payFreqIndex], stockFiles[selectedStockIndex], reinvestStatus);
 // Adjust date if necessary
        int dayIndex = 1;
        while (!newInvestment->valid_start_date(startDate)) {
            startDate = std::to_string(day + dayIndex) + "/" + std::to_string(month) + "/" + std::to_string(year);
            newInvestment->set_start_date(startDate);  // Assume a set_start_date function exists for date updates
            newInvestment = new Dividend(startDate, capitalInvestment, payFreqOptions[payFreqIndex], stockFiles[selectedStockIndex], reinvestStatus);
            dayIndex++;
            if (dayIndex == 10) break;
        }
} else if (investmentIndex == 1){
     newInvestment = new Momentum(startDate, capitalInvestment, stockFiles[selectedStockIndex], period);

                int dayIndex = 1;
            while (!newInvestment->valid_start_date(startDate)) {
                startDate = std::to_string(day + dayIndex) + "/" + std::to_string(month) + "/" + std::to_string(year);
                newInvestment = new Momentum(startDate, capitalInvestment, stockFiles[selectedStockIndex], period);
                dayIndex++;
                if (dayIndex == 10) break;
            }
} else if (investmentIndex == 2){
    newInvestment = new SetDeposit(startDate, stockFiles[selectedStockIndex], capitalInvestment);

                int dayIndex = 1;
            while (!newInvestment->valid_start_date(startDate)) {
                startDate = std::to_string(day + dayIndex) + "/" + std::to_string(month) + "/" + std::to_string(year);
                newInvestment = new SetDeposit(startDate, stockFiles[selectedStockIndex], capitalInvestment);
                dayIndex++;
                if (dayIndex == 10) break;
            }
} else if (investmentIndex == 3){
        newInvestment = new MovingAverageCrossover(startDate, capitalInvestment, stockFiles[selectedStockIndex], period, secondPeriod);

                int dayIndex = 1;
            while (!newInvestment->valid_start_date(startDate)) {
                startDate = std::to_string(day + dayIndex) + "/" + std::to_string(month) + "/" + std::to_string(year);
            newInvestment = new MovingAverageCrossover(startDate, capitalInvestment, stockFiles[selectedStockIndex], period, secondPeriod);
            dayIndex++;
                if (dayIndex == 10) break;
            }
}
        finalCapital = newInvestment->get_final_capital();
        showFinalCapitalPopup = true;
        ImGui::OpenPopup("Investment Result");
    }
}
    

    // Display the popup modal with Final Capital
    if (showFinalCapitalPopup) {
        if (ImGui::BeginPopupModal("Investment Result", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::Text("Inital Capital: $%.2f", capitalInvestment);
            ImGui::Text("Final Capital: $%.2f", finalCapital);
            ImGui::Text("Total Profit: $%.2f", capitalProfit);

            if(ImGui::Button("Add to Portfolio")) {
                portfolio.add_investment(newInvestment);  // Add investment to portfolio
                showFinalCapitalPopup = false;
                ImGui::CloseCurrentPopup();
                currentScreen = 0;
                investmentIndex = -1;
                selectedStockIndex = -1;
                day = 1;
                month = 1;
                year = 2024;
                period = 0.0f;
                secondPeriod = 0.0f;
                capitalInvestment = 0.0f;
                bank = bank + capitalProfit;
            }

            if (ImGui::Button("Try another Investment")) {
                showFinalCapitalPopup = false;
                ImGui::CloseCurrentPopup();
                currentScreen = 3;
                investmentIndex = -1;
                day = 1;
                month = 1;
                year = 2024;
                period = 0.0f;
                secondPeriod = 0.0f;
                capitalInvestment = 0.0f;
            }
            ImGui::EndPopup();
        } else {
            // Debug to confirm the popup attempt
            std::cout << "Popup model is active but not visible." << std::endl;;
        }
    }





// Pop styling
ImGui::PopStyleColor(4);
ImGui::PopStyleVar(3);

            

            ImGui::SetCursorPos(ImVec2((5),(575)));
            if (ImGui::Button("Go Back")) {
                currentScreen = 3; 
                day = 1;
                month = 1;
                year = 2024;
                period = 0.0f;
                secondPeriod = 0.0f;
                capitalInvestment = 0.0f;
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
 