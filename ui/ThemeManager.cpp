#include <QStyle>
#include <QApplication>
#include <QStyleFactory>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QFile>
#include <QDir>

#include "ThemeManager.hpp"

// Define static theme constants
const QString ThemeManager::THEME_SYSTEM = "0";
const QString ThemeManager::THEME_MODERN_DARK = "modern_dark";
const QString ThemeManager::THEME_MODERN_LIGHT = "modern_light";
const QString ThemeManager::THEME_AMOLED = "amoled";

ThemeManager *themeManager = new ThemeManager;

extern QString ReadFileText(const QString &path);

void ThemeManager::ApplyTheme(const QString &theme) {
    auto internal = [=] {
        if (this->system_style_name.isEmpty()) {
            this->system_style_name = qApp->style()->objectName();
        }
        if (this->current_theme == theme) {
            return;
        }

        bool ok;
        auto themeId = theme.toInt(&ok);
        QString qss;

        if (ok) {
            // System & Built-in themes
            if (themeId != 0) {
                QString path;
                std::map<QString, QString> replace;
                switch (themeId) {
                    case 1:
                        path = ":/themes/feiyangqingyun/qss/flatgray.css";
                        replace[":/qss/"] = ":/themes/feiyangqingyun/qss/";
                        break;
                    case 2:
                        path = ":/themes/feiyangqingyun/qss/lightblue.css";
                        replace[":/qss/"] = ":/themes/feiyangqingyun/qss/";
                        break;
                    case 3:
                        path = ":/themes/feiyangqingyun/qss/blacksoft.css";
                        replace[":/qss/"] = ":/themes/feiyangqingyun/qss/";
                        break;
                    default:
                        return;
                }
                qss = ReadFileText(path);
                for (auto const &[a, b]: replace) {
                    qss = qss.replace(a, b);
                }
            }

            auto system_style = QStyleFactory::create(this->system_style_name);

            if (themeId == 0) {
                // system theme
                qApp->setPalette(system_style->standardPalette());
                qApp->setStyle(system_style);
                qApp->setStyleSheet("");
            } else {
                if (themeId >= 1 && themeId <= 3) {
                    // feiyangqingyun theme
                    QString paletteColor = qss.mid(20, 7);
                    qApp->setPalette(QPalette(paletteColor));
                } else {
                    // other theme
                    qApp->setPalette(system_style->standardPalette());
                }
                qApp->setStyleSheet(qss);
            }
        } else {
            // Modern themes (Qt 6 style)
            if (theme == THEME_MODERN_DARK) {
                qss = ReadFileText(":/themes/modern/dark.css");
                dark_mode_enabled = true;
            } else if (theme == THEME_MODERN_LIGHT) {
                qss = ReadFileText(":/themes/modern/light.css");
                dark_mode_enabled = false;
            } else if (theme == THEME_AMOLED) {
                qss = ReadFileText(":/themes/modern/amoled.css");
                dark_mode_enabled = true;
            } else {
                // QStyleFactory fallback
                const auto &_style = QStyleFactory::create(theme);
                if (_style != nullptr) {
                    qApp->setPalette(_style->standardPalette());
                    qApp->setStyle(_style);
                    qApp->setStyleSheet("");
                }
                current_theme = theme;
                return;
            }
            
            // Apply modern theme stylesheet
            if (!qss.isEmpty()) {
                qApp->setStyleSheet(qss);
            }
        }

        // Apply custom background if set
        if (!custom_background_path.isEmpty()) {
            ApplyCustomBackground();
        }

        current_theme = theme;
    };
    internal();

    // Append NekoRay specific styles
    auto nekoray_css = ReadFileText(":/neko/neko.css");
    if (!nekoray_css.isEmpty()) {
        qApp->setStyleSheet(qApp->styleSheet().append("\n").append(nekoray_css));
    }
}

void ThemeManager::SetCustomBackground(const QString &imagePath) {
    custom_background_path = imagePath;
    ApplyCustomBackground();
}

void ThemeManager::ApplyCustomBackground() {
    if (custom_background_path.isEmpty()) {
        // Remove background if path is empty
        qApp->setPalette(QPalette(QColor("#1a1b26")));
        return;
    }
    
    QPixmap bg(custom_background_path);
    if (!bg.isNull()) {
        // Background is applied via MainWindow's central widget
        // This method sets up the configuration
        emit backgroundChanged();
    }
}

void ThemeManager::SetBackgroundOpacity(double opacity) {
    background_opacity = qBound(0.0, opacity, 1.0);
    if (!custom_background_path.isEmpty()) {
        ApplyCustomBackground();
    }
}

void ThemeManager::EnableAnimations(bool enabled) {
    animations_enabled = enabled;
    // Qt animation settings can be configured globally here
}

void ThemeManager::ToggleDarkMode() {
    dark_mode_enabled = !dark_mode_enabled;
    ApplyTheme(dark_mode_enabled ? THEME_MODERN_DARK : THEME_MODERN_LIGHT);
}

void ThemeManager::FadeInWidget(QWidget *widget, int duration) {
    if (!widget || !animations_enabled) return;
    
    auto effect = new QGraphicsOpacityEffect(widget);
    widget->setGraphicsEffect(effect);
    
    auto anim = new QPropertyAnimation(effect, "opacity");
    anim->setDuration(duration);
    anim->setStartValue(0.0);
    anim->setEndValue(1.0);
    anim->setEasingCurve(QEasingCurve::InOutQuad);
    anim->start(QPropertyAnimation::DeleteWhenStopped);
}

void ThemeManager::FadeOutWidget(QWidget *widget, int duration) {
    if (!widget || !animations_enabled) return;
    
    auto effect = new QGraphicsOpacityEffect(widget);
    widget->setGraphicsEffect(effect);
    
    auto anim = new QPropertyAnimation(effect, "opacity");
    anim->setDuration(duration);
    anim->setStartValue(1.0);
    anim->setEndValue(0.0);
    anim->setEasingCurve(QEasingCurve::InOutQuad);
    anim->start(QPropertyAnimation::DeleteWhenStopped);
}
