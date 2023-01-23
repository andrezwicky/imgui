#pragma once
#include "imgui_internal.h"
#include <utility>
#include <string>
#include <vector>

namespace ImGui
{
    void ColorfulText(const std::string& text, const std::pmr::vector<std::pair<char, ImVec4>>& colors = {});
}

namespace TextColors
{
    static const ImVec4&
        white = { 1,1,1,1 },
        blue = { 0.000f, 0.703f, 0.917f,1 },
        red = { 0.976f, 0.117f, 0.265f ,1 },
        grey = { 0.230f, 0.226f, 0.289f,1 },
        lgrey = { 0.9f, 0.9f, 0.9f,1 },
        green = { 0.000f, 0.386f, 0.265f,1 },
        lime = { 0.55f, 0.90f, 0.06f,1 },
        yellow = { 1.0f, 0.9f, 0.21f,1 },
        purple = { 1,0,1,1 },
        orange = { 1.00f, 0.36f, 0.09f,1 };


    const std::pmr::vector<std::pair<char, ImVec4>> seqlist =
    { {'o', white} , { 'x', yellow }, { 'h', lgrey } };
}

