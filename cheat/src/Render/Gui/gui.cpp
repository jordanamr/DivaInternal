#include "gui.h"
#include "global.h"
#include "imgui.h"
#include "Utils.h"
#include "utils/gui-util.hpp"

void Gui::Render()
{
	auto& vars = Vars::GetInstance();
	
    ImGui::Begin(xorstr("##DivaInternal"), nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
    {
        ImGui::BeginGroup();
        {
            ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0, 0, 0, 0));
            GuiUtil::CenterText(xorstr("DivaInternal"), 0, 0);
            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::PopStyleColor();
        }
        ImGui::EndGroup();

		GuiUtil::RainbowLine();
		ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0, 0, 0, 0));
		ImGui::BeginChild(xorstr("##LeftSide"), ImVec2(100, GuiUtil::GetY()), TRUE);
		ImGui::PopStyleColor();
		{
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

#define MENU_MODULES(name, tab) ImGui::PushStyleColor(ImGuiCol_Button, m_MenuTab == (tab) ? active : inactive); \
		     ImGui::Button(name, ImVec2(90 - 10, 22)); \
		     if (ImGui::IsItemClicked()) m_MenuTab = tab; \
		     ImGui::PopStyleColor()

			MENU_MODULES(xorstr("Features"), 0);
			MENU_MODULES(xorstr("Hotkeys"), 1);
			MENU_MODULES(xorstr("About"), 2);

#undef MENU_MODULES
		}
		ImGui::EndChild();

		GuiUtil::LineVertical();

		ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0, 0, 0, 0));
		ImGui::BeginChild(xorstr("##RightSide"), ImVec2(GuiUtil::GetX(), GuiUtil::GetY()), TRUE);
		ImGui::PopStyleColor();
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImGuiCol_Button ? active : inactive);
		switch (m_MenuTab)
		{
		case 0: // Features
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
			ImGui::BeginGroup();
			ImGui::CheckboxFill(xorstr("Pipe Server"), &vars.PipeServer.value()); HELPMAKER(xorstr("To be used with DivaBot"));
			if (vars.PipeServer.value()) {
				static char pipeNameBuffer[256];
				strncpy_s(pipeNameBuffer, vars.PipeServerName.value().c_str(), sizeof(pipeNameBuffer));
				pipeNameBuffer[sizeof(pipeNameBuffer) - 1] = '\0';
				if (ImGui::InputText("Pipe name", pipeNameBuffer, sizeof(pipeNameBuffer))) {
					vars.PipeServerName.value() = std::string(pipeNameBuffer);
				} HELPMAKER(xorstr("If you change this, you need to restart the game"));
			}
			ImGui::CheckboxFill(xorstr("Redirect connect()"), &vars.RedirectConnect.value()); HELPMAKER(xorstr("Redirect any connection to 5555 on a specific address"));
			if (vars.RedirectConnect.value()) {
				static char addressBuffer[256];
				strncpy_s(addressBuffer, vars.RedirectConnectAddress.value().c_str(), sizeof(addressBuffer));
				addressBuffer[sizeof(addressBuffer) - 1] = '\0';
				if (ImGui::InputText("Address", addressBuffer, sizeof(addressBuffer))) {
					vars.RedirectConnectAddress.value() = std::string(addressBuffer);
				}
			}
			ImGui::CheckboxFill(xorstr("Fight anti-AFK"), &vars.FightAntiAFK.value()); HELPMAKER(xorstr("Disable the inactivity popup in fights"));
			ImGui::EndGroup();
			ImGui::PopStyleVar();
			break;
		case 1: // Hotkeys
			ImGui::InputHotkey(xorstr("Pipe Server"), vars.PipeServer);
			ImGui::InputHotkey(xorstr("Redirect connect()"), vars.RedirectConnect);
			ImGui::InputHotkey(xorstr("Fight anti-AFK"), vars.FightAntiAFK);
			break;
		case 2: // About
			ImGui::Spacing();
			ImGui::Text(xorstr("DivaInternal - Fucking Dofus 3 since 2024"));
			ImGui::Text(xorstr("Made with love by Aristochat"));
			ImGui::TextURL(xorstr("Thanks to Taiga74164 for the ImGUI design"), xorstr("https://github.com/Taiga74164/SLA-Cheeto"));
			break;
		}

		ImGui::PopStyleColor();
		ImGui::EndChild();
    }

    ImGui::End();
}