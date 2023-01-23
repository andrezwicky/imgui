#pragma once
#include "imgui_colorfultext.h"

namespace ImGui
{
    void ColorfulText(const std::string& text, const std::pmr::vector<std::pair<char, ImVec4>>& colors)
    {
        auto p = ImGui::GetCursorScreenPos();
        const auto first_px = p.x, first_py = p.y;
        auto im_colors = ImGui::GetStyle().Colors;
        const auto default_color = im_colors[ImGuiCol_Text];
        std::string temp_str;
        struct text_t {
            ImVec4 color;
            std::string text;
        };
        std::pmr::vector<text_t> texts;
        bool color_time = false;
        ImVec4 last_color = default_color;
        for (const auto& i : text) {
            if (color_time) {
                const auto& f = std::find_if(colors.begin(), colors.end(), [i](const auto& v) { return v.first == i; });
                if (f != colors.end())
                    last_color = f->second;
                else
                    temp_str += i;
                color_time = false;
                continue;
            };
            switch (i) {
            case '$':
                color_time = true;
                if (!temp_str.empty()) {
                    texts.push_back({ last_color, temp_str });
                    temp_str.clear();
                };
                break;
            default:
                temp_str += i;
            };
        };
        if (!temp_str.empty()) {
            texts.push_back({ last_color, temp_str });
            temp_str.clear();
        };
        float max_x = p.x;
        for (const auto& i : texts) {
            im_colors[ImGuiCol_Text] = i.color;
            std::pmr::vector<std::string> lines;
            temp_str.clear();
            for (const auto& lc : i.text) {
                if (lc == '\n') {
                    lines.push_back(temp_str += lc);
                    temp_str.clear();
                }
                else
                    temp_str += lc;
            };
            bool last_is_line = false;
            if (!temp_str.empty())
                lines.push_back(temp_str);
            else
                last_is_line = true;
            float last_px = 0.f;
            for (const auto& j : lines) {
                ImGui::RenderText(p, j.c_str());
                p.y += 15.f;
                last_px = p.x;
                max_x = (max_x < last_px) ? last_px : max_x;
                p.x = first_px;
            };
            const auto& last = lines.back();
            if (last.back() != '\n')
                p.x = last_px;
            else
                p.x = first_px;
            if (!last_is_line)
                p.y -= 15.f;
            if (i.text.back() != '\n')
                p.x += ImGui::CalcTextSize(last.c_str()).x;
        };
        im_colors[ImGuiCol_Text] = default_color;
        ImGui::Dummy({ max_x - p.x, p.y - first_py });
    };
}


