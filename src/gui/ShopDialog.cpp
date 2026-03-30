
#include "ShopDialog.hpp"

#include <QFrame>
#include <QGraphicsColorizeEffect>
#include <QHBoxLayout>
#include <QPixmap>
#include <QPushButton>

namespace NomCool::gui {

ShopDialog::ShopDialog(data::SkinManager &skinManager,
                       data::Experience &experience, QWidget *parent)
    : QDialog(parent), mSkinManager(skinManager), mExperience(experience) {
  setWindowTitle("Shop");
  setMinimumWidth(350);

  auto *mainLayout = new QVBoxLayout();

  mGoldLabel = new QLabel();
  mGoldLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #DAA520;");
  mainLayout->addWidget(mGoldLabel);

  auto *separator = new QFrame();
  separator->setFrameShape(QFrame::HLine);
  mainLayout->addWidget(separator);

  mItemsLayout = new QVBoxLayout();
  mainLayout->addLayout(mItemsLayout);

  mainLayout->addStretch();
  setLayout(mainLayout);

  rebuildItems();
}

void ShopDialog::rebuildItems() {
  mGoldLabel->setText(QString("Gold: %1").arg(mExperience.gold()));

  // Clear existing items
  while (mItemsLayout->count() > 0) {
    auto *item = mItemsLayout->takeAt(0);
    if (item->widget())
      item->widget()->deleteLater();
    delete item;
  }

  const auto &skins = mSkinManager.allSkins();
  QPixmap baseMascot(":/mascot/mascot.png");

  for (int i = 0; i < static_cast<int>(skins.size()); ++i) {
    const auto &skin = skins[i];

    auto *row = new QFrame();
    row->setFrameShape(QFrame::StyledPanel);
    auto *rowLayout = new QHBoxLayout();

    // Mini preview
    auto *preview = new QLabel();
    QPixmap previewPixmap = baseMascot.scaledToHeight(50, Qt::SmoothTransformation);

    if (skin.tint.alpha() > 0) {
      // Apply tint to preview by painting
      QImage img = previewPixmap.toImage();
      for (int y = 0; y < img.height(); ++y) {
        for (int x = 0; x < img.width(); ++x) {
          QColor pixel(img.pixelColor(x, y));
          if (pixel.alpha() > 0) {
            int r = (pixel.red() + skin.tint.red()) / 2;
            int g = (pixel.green() + skin.tint.green()) / 2;
            int b = (pixel.blue() + skin.tint.blue()) / 2;
            img.setPixelColor(x, y, QColor(r, g, b, pixel.alpha()));
          }
        }
      }
      previewPixmap = QPixmap::fromImage(img);
    }

    preview->setPixmap(previewPixmap);
    preview->setFixedSize(60, 60);
    preview->setAlignment(Qt::AlignCenter);
    rowLayout->addWidget(preview);

    // Name + price
    auto *infoLayout = new QVBoxLayout();
    auto *nameLabel = new QLabel(skin.name);
    nameLabel->setStyleSheet("font-weight: bold;");
    infoLayout->addWidget(nameLabel);

    if (skin.price > 0) {
      auto *priceLabel =
          new QLabel(QString("%1 gold").arg(skin.price));
      priceLabel->setStyleSheet("color: #DAA520;");
      infoLayout->addWidget(priceLabel);
    } else {
      auto *freeLabel = new QLabel("Free");
      freeLabel->setStyleSheet("color: grey;");
      infoLayout->addWidget(freeLabel);
    }
    rowLayout->addLayout(infoLayout);

    rowLayout->addStretch();

    // Action button
    if (mSkinManager.isOwned(i)) {
      auto *ownedLabel = new QLabel("Owned");
      ownedLabel->setStyleSheet(
          "color: #4CAF50; font-weight: bold; padding: 5px;");
      rowLayout->addWidget(ownedLabel);
    } else {
      auto *buyButton = new QPushButton(
          QString("Buy (%1g)").arg(skin.price));
      bool canAfford = mExperience.gold() >= skin.price;
      buyButton->setEnabled(canAfford);
      if (!canAfford) {
        buyButton->setStyleSheet("color: grey;");
      } else {
        buyButton->setStyleSheet(
            "background-color: #DAA520; color: white; font-weight: bold; "
            "padding: 5px 10px;");
      }

      connect(buyButton, &QPushButton::clicked, this, [this, i] {
        int gold = mExperience.gold();
        if (mSkinManager.purchase(i, gold)) {
          mExperience.spendGold(mExperience.gold() - gold);
          emit skinPurchased();
          rebuildItems();
        }
      });
      rowLayout->addWidget(buyButton);
    }

    row->setLayout(rowLayout);
    mItemsLayout->addWidget(row);
  }
}

} // namespace NomCool::gui
