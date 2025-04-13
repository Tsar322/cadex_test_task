#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <sstream>
#include <curves/curves.h>

void printCurve(const curves::Curve* curve) {
    if (const auto* circle = dynamic_cast<const curves::Circle*>(curve)) {
        std::cout << "Circle: radius = " << std::fixed << std::setprecision(2)
            << circle->radius() << '\t';
    }
    else if (const auto* ellipse = dynamic_cast<const curves::Ellipse*>(curve)) {
        std::cout << "Ellipse: radiusX = " << std::fixed << std::setprecision(2)
            << ellipse->radiusX() << ", radiusY = "
            << ellipse->radiusY() << '\t';
    }
    else if (const auto* helix = dynamic_cast<const curves::Helix*>(curve)) {
        std::cout << "Helix: radius = " << std::fixed << std::setprecision(2)
            << helix->radius() << ", step = "
            << helix->step() << '\t';
    }
    else {
        std::cout << "Unknown curve type" << '\t';
    }
}

template<typename T>
size_t calculateColumnWidth(const std::vector<T>& values) {
    if (values.empty()) return 0;

    size_t max_width = 0;
    for (const auto& val : values) {
        std::ostringstream oss;
        oss << val;
        max_width = std::max(max_width, oss.str().length());
    }
    return max_width + 2; // +2 для отступов
}

void printCurvesTable(const std::vector<std::shared_ptr<curves::Curve>>& curves, double t) {
    // Собираем данные
    std::vector<std::vector<std::string>> rows;
    size_t col_widths[4] = { 6, 8, 20, 20 }; // Минимальные ширины для Type, Params, Point, Derivative

    // Заголовки столбцов
    rows.push_back({
        "Type",
        "Params",
        "Point (t=" + std::to_string(t) + ")",
        "Derivative"
        });

    // Заполняем данные
    for (const auto& curve : curves) {
        std::string type;
        std::string params;

        if (auto c = dynamic_cast<const curves::Circle*>(curve.get())) {
            type = "Circle";
            params = "r=" + std::to_string(c->radius());
        }
        else if (auto e = dynamic_cast<const curves::Ellipse*>(curve.get())) {
            type = "Ellipse";
            params = "rx=" + std::to_string(e->radiusX()) + " ry=" + std::to_string(e->radiusY());
        }
        else if (auto h = dynamic_cast<const curves::Helix*>(curve.get())) {
            type = "Helix";
            params = "r=" + std::to_string(h->radius()) + " step=" + std::to_string(h->step());
        }

        std::ostringstream point, deriv;
        point << curve->point3D(t);
        deriv << curve->firstDerivative(t);

        rows.push_back({ type, params, point.str(), deriv.str() });

        // Обновляем максимальные ширины
        col_widths[0] = std::max(col_widths[0], type.length());
        col_widths[1] = std::max(col_widths[1], params.length());
        col_widths[2] = std::max(col_widths[2], point.str().length());
        col_widths[3] = std::max(col_widths[3], deriv.str().length());
    }

    // Добавляем отступы
    for (auto& w : col_widths) w += 2;

    // Функция для печати разделительной линии
    auto print_line = [&]() {
        std::cout << "+";
        for (size_t w : col_widths) {
            std::cout << std::string(w, '-') << "+";
        }
        std::cout << "\n";
        };

    // Печатаем таблицу
    print_line();

    // Заголовки
    std::cout << "| " << std::left << std::setw(col_widths[0] - 1) << rows[0][0]
        << "| " << std::setw(col_widths[1] - 1) << rows[0][1]
        << "| " << std::setw(col_widths[2] - 1) << rows[0][2]
        << "| " << std::setw(col_widths[3] - 1) << rows[0][3] << "|\n";

    print_line();

    // Данные
    for (size_t i = 1; i < rows.size(); ++i) {
        std::cout << "| " << std::setw(col_widths[0] - 1) << rows[i][0]
            << "| " << std::setw(col_widths[1] - 1) << rows[i][1]
            << "| " << std::setw(col_widths[2] - 1) << rows[i][2]
            << "| " << std::setw(col_widths[3] - 1) << rows[i][3] << "|\n";
    }

    print_line();
}