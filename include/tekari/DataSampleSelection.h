#pragma once

#include <nanogui/opengl.h>
#include <tbb/parallel_for.h>
#include "SelectionBox.h"
#include "PointSampleInfo.h"
#include "delaunay.h"

TEKARI_NAMESPACE_BEGIN

enum SelectionMode
{
    STANDARD,
    ADD,
    SUBTRACT
};

extern void select_points(
    const std::vector<nanogui::Vector3f> &rawPoints,
    const std::vector<del_point2d_t> &V2D,
    const std::vector<float> &H,
    std::vector<uint8_t> &selectedPoints,
    const nanogui::Matrix4f & mvp,
    const SelectionBox& selectionBox,
    const nanogui::Vector2i & canvasSize,
    SelectionMode mode
);

extern void select_closest_point(
    const std::vector<nanogui::Vector3f> &rawPoints,
    const std::vector<del_point2d_t> &V2D,
    const std::vector<float> &heights,
    std::vector<uint8_t> &selectedPoints,
    const nanogui::Matrix4f& mvp,
    const nanogui::Vector2i & mousePos,
    const nanogui::Vector2i & canvasSize
);

extern void select_highest_point(
    const PointSampleInfo &pointsInfo,
    const PointSampleInfo &selectionInfo,
    std::vector<uint8_t> &selectedPoints
);

extern void deselect_all_points(std::vector<uint8_t> &selectedPoints);

extern void update_selection_info(
    PointSampleInfo &selectionInfo,
    const std::vector<uint8_t> &selectedPoints,
    const std::vector<nanogui::Vector3f> &rawPoints,
    const std::vector<del_point2d_t> &V2D,
    const std::vector<float> &H
);

extern void move_selection_along_path(
    bool up,
    std::vector<uint8_t> &selectedPoints
);

extern void delete_selected_points(
    std::vector<uint8_t> &selectedPoints,
    std::vector<nanogui::Vector3f> &rawPoints,
    std::vector<del_point2d_t> &V2D
);

TEKARI_NAMESPACE_END