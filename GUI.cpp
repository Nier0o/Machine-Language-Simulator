#include "GUI.h"
void GUI::show()
{
    static char userInput[1024];

    ImGui::SetNextWindowSize(ImVec2(400, 400), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("Data Input Window")) {


        ImGui::InputTextMultiline("##UserInput", userInput, IM_ARRAYSIZE(userInput), ImVec2(-1.0f, -1.0f));


    }ImGui::End();

    ImGui::SetNextWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("Register")) {

        if (ImGui::BeginTable("Register Cells", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
            for (int col = 0; col < 2; ++col) {
                string column = "";
                if (col == 0) ImGui::TableSetupColumn(column.c_str(), ImGuiTableColumnFlags_WidthFixed, 40.0f);
                else
                {
                    char c = ((col - 1) < 10) ? ('0' + col - 1) : ('7' + col - 1);
                    column += 'R';
                    ImGui::TableSetupColumn(column.c_str(), ImGuiTableColumnFlags_WidthFixed, 40.0f);
                }
            }

            ImGui::TableHeadersRow();

            for (int row = 0; row < 16; ++row) {
                ImGui::TableNextRow();

                for (int col = 0; col < 2; ++col) {
                    if (col == 0)
                    {
                        char c = (row < 10) ? ('0' + row) : ('7' + row);
                        string rowStr = "";
                        rowStr += c;
                        ImGui::TableSetColumnIndex(col);
                        ImGui::Text(rowStr.c_str(), row, col);
                    }
                    else
                    {
                        char c1 = (row < 10) ? ('0' + row) : ('7' + row);
                        string data = voleMachine.getMemoryRegister(c1);
                        ImGui::TableSetColumnIndex(col);
                        ImGui::Text(data.c_str());
                    }
                }
            }

            ImGui::EndTable();
       

        }

    }ImGui::End();

    ImGui::SetNextWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("Main Memory")) {

        if (ImGui::BeginTable("Memory Cells", 17, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
            for (int col = 0; col < 17; ++col) {
                string column = "";
                if (col == 0) ImGui::TableSetupColumn(column.c_str(), ImGuiTableColumnFlags_WidthFixed, 40.0f);
                else
                {
                    char c = ((col - 1) < 10) ? ('0' + col - 1) : ('7' + col - 1);
                    column += c;
                    ImGui::TableSetupColumn(column.c_str(), ImGuiTableColumnFlags_WidthFixed, 40.0f);
                }
            }

            ImGui::TableHeadersRow();

            for (int row = 0; row < 16; ++row) {
                ImGui::TableNextRow();

                for (int col = 0; col < 17; ++col) {
                    if (col == 0)
                    {
                        char c = (row < 10) ? ('0' + row) : ('7' + row);
                        string rowStr = "";
                        rowStr += c;
                        ImGui::TableSetColumnIndex(col);
                        ImGui::Text(rowStr.c_str(), row, col);
                    }
                    else
                    {
                        char c1 = (row < 10) ? ('0' + row) : ('7' + row);
                        char c2 = ((col - 1) < 10) ? ('0' + col - 1) : ('7' + col - 1);
                        string str = "";
                        str += c1; str += c2;
                        string data = voleMachine.getMemoryCell(str);
                        ImGui::TableSetColumnIndex(col);
                        ImGui::Text(data.c_str());
                    }
                }
            }

            ImGui::EndTable();
        }

    }ImGui::End();

    ImGui::SetNextWindowSize(ImVec2(300, 100), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("CPU")) {

        ImGui::Text("PC :");

        ImGui::SameLine();
        ImGui::Text("%d", voleMachine.getCounter());

        ImGui::NewLine;

        ImGui::Text("IR :");

        ImGui::SameLine();
        ImGui::Text(voleMachine.getInstruction().c_str());

        
    }ImGui::End();


    ImGui::SetNextWindowSize(ImVec2(300, 100), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("Commands")) {
        bool loadMainMemory = false;

        if (ImGui::Button("Load Data")) {
            loadMainMemory = true;
        }

        if (loadMainMemory) {
            voleMachine.loadProgramInput(userInput);
            loadMainMemory = false;
        }

        bool runSingleStep = false;

        if (ImGui::Button("Single step")) {
            runSingleStep = true;
        }

        if (runSingleStep) {
            if (!voleMachine.getHalt())
            {
                voleMachine.fetchProgramInstruction();
                voleMachine.executeProgramInstrction();
            }
            runSingleStep = false;
        }

        ImGui::NewLine;
        ImGui::NewLine;

        bool runProgram = false;

        if (ImGui::Button("Run")) {
            runProgram = true;
        }

        if (runProgram) {
            while (!voleMachine.getHalt())
            {
                voleMachine.fetchProgramInstruction();
                voleMachine.executeProgramInstrction();
            }

            runProgram = false;
        }

        ImGui::NewLine;
        ImGui::NewLine;

        bool haltProgram = false;

        if (ImGui::Button("Halt")) {
            haltProgram = true;
        }

        if (haltProgram) {
            voleMachine.setHalt(1);
            
            haltProgram = false;
        }
        
        if (voleMachine.getHalt())
        {
            ImGui::SetNextWindowSize(ImVec2(300, 100), ImGuiCond_FirstUseEver);
            if (ImGui::Begin("Halt")) {

                ImGui::Text("Program was halted or finished");

            }ImGui::End();
        }
       

    }ImGui::End();
}
 
