
add_library( base
  resources/icons/ko.png resources/icons/ok.png resources/resource.qrc
  resources/icons/ko.png resources/icons/ok.png resources/resource.qrc
  resources/icons/ko.png resources/icons/ok.png resources/mascot/mascot.png resources/resource.qrc )

target_sources( base
  PRIVATE
    gui/MainWindow.cpp gui/Interrogation.cpp gui/PreviousResult.cpp gui/ScoreDisplay.cpp gui/QuestionTimer.cpp gui/DifficultySelector.cpp gui/Mascot.cpp gui/MascotManager.cpp
)
target_sources( base
  PRIVATE
    data/Interrogation.cpp data/Result.cpp data/Score.cpp data/QuestionGenerator.cpp
)

target_sources( base
  PRIVATE
    resources/resource.qrc
)

target_include_directories( base
  PUBLIC "." )

target_link_libraries( base PUBLIC Qt6::Widgets )

add_executable( ${PROJECT_NAME}
                main.cpp )

target_link_libraries( ${PROJECT_NAME} PRIVATE base Qt6::Widgets Qt6::Core )
