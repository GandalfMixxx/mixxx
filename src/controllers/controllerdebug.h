#ifndef CONTROLLERDEBUG_H
#define CONTROLLERDEBUG_H

#include <QDebug>
#include <QApplication>

class ControllerDebug {
  public:
      static ControllerDebug& instance() {
          static ControllerDebug instance;
          return instance;
      }

      static bool enabled() {
          return instance().m_enabled;
      }

      static void setEnabled(bool enabled) {
          instance().m_enabled = enabled;
      }

  private:
    ControllerDebug() {
        // Get --controllerDebug command line option
        QStringList commandLineArgs = QApplication::arguments();
        m_enabled = commandLineArgs.contains("--controllerDebug", Qt::CaseInsensitive) ||
                commandLineArgs.contains("--midiDebug", Qt::CaseInsensitive);
    }

    // Specifies whether or not we should dump incoming data to the console at
    // runtime. This is useful for end-user debugging and script-writing.
    bool m_enabled;
};

// Usage
// controllerDebug("hello" << "world");
#define controllerDebug(stream)       \
{                                     \
    if (ControllerDebug::enabled()) { \
        QDebug(QtDebugMsg) << stream; \
    }                                 \
}                                     \

#endif // CONTROLLERDEBUG_H
