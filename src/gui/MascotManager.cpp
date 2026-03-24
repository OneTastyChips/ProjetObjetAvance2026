
#include "MascotManager.hpp"

#include <QCheckBox>
#include <QVBoxLayout>

namespace NomCool::gui {

MascotManager::MascotManager() {
  auto *layout = new QVBoxLayout();

  auto *toggle = new QCheckBox("Show mascot");
  toggle->setChecked(true);
  layout->addWidget(toggle);

  mMascot = new Mascot();
  layout->addWidget(mMascot);

  connect(toggle, &QCheckBox::toggled, mMascot, &Mascot::setVisible);

  setLayout(layout);
}

} // namespace NomCool::gui
