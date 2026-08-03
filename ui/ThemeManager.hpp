#pragma once

#include <QString>
#include <QObject>
#include <QPixmap>
#include <QOpacityEffect>

class ThemeManager {
public:
    QString system_style_name = "";
    QString current_theme = "0"; // int: 0:system 1+:builtin string: QStyleFactory
    
    // Modern theme options
    bool dark_mode_enabled = true;
    bool animations_enabled = true;
    QString custom_background_path = "";
    double background_opacity = 0.85;
    
    // Available modern themes
    static const QString THEME_SYSTEM;
    static const QString THEME_MODERN_DARK;
    static const QString THEME_MODERN_LIGHT;
    static const QString THEME_AMOLED;
    
    void ApplyTheme(const QString &theme);
    void SetCustomBackground(const QString &imagePath);
    void SetBackgroundOpacity(double opacity);
    void EnableAnimations(bool enabled);
    void ToggleDarkMode();
    
    // Animation helpers
    static void FadeInWidget(QWidget *widget, int duration = 300);
    static void FadeOutWidget(QWidget *widget, int duration = 300);
};

extern ThemeManager *themeManager;
