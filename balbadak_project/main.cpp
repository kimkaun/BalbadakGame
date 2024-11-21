#include <SFML/Graphics.hpp>
#include <locale>  // 로케일 설정을 위해 추가
#include "level.cpp"  // level.cpp 파일 포함
#include "easy.cpp"   // easy.cpp 파일 포함

// 열거형
enum class GameState {
    Start,
    Level,
    Easy
};

// 한국어 적용 및 창 크기, 제목
int main() {
    std::locale::global(std::locale("ko_KR.UTF-8"));
    sf::RenderWindow window(sf::VideoMode(800, 500), "Cat Paw Tap Game");
    
    // 열거형의 start 상태로 초기화(게임의 현재 상태를 추적 가능)
    GameState gameState = GameState::Start;

    // 폰트 로드
    sf::Font font;
    if (!font.loadFromFile("C:\\work\\c++_projects\\balbadak_project\\font\\ongelyp.ttf")) {
        return -1;
    }

    // 발바닥 이미지 설정
    sf::Texture pawTexture;
    sf::Sprite pawSprite;
    if (pawTexture.loadFromFile("C:\\work\\c++_projects\\balbadak_project\\img\\pink_balbadak.png")) {
        pawSprite.setTexture(pawTexture);
        pawSprite.setPosition(98, 187);  // 발바닥 이미지 위치 설정
        pawSprite.setScale(85.0f / pawSprite.getLocalBounds().width, 81.0f / pawSprite.getLocalBounds().height);  // 크기 조정
    }

    // Start 화면 제목
    sf::Text startText;
    startText.setFont(font);
    startText.setString(L"고양이 발바닥 게임");
    startText.setCharacterSize(96);
    startText.setFillColor(sf::Color::Black);
    startText.setPosition(140, 190);

    // 버튼 사각형
    sf::RectangleShape startButton(sf::Vector2f(161, 55));
    startButton.setFillColor(sf::Color(134, 145, 244));
    startButton.setPosition(320, 372);

    // 버튼 텍스트
    sf::Text startButtonText;
    startButtonText.setFont(font);
    startButtonText.setString(L"게임시작");
    startButtonText.setCharacterSize(55);
    startButtonText.setFillColor(sf::Color::White);
    startButtonText.setPosition(329, 362);


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Start 화면에서 Start 버튼 클릭
            if (gameState == GameState::Start &&
                event.type == sf::Event::MouseButtonPressed &&
                startButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                gameState = GameState::Level;
            }
        }

        if (gameState == GameState::Start) {
            window.clear(sf::Color(222, 231, 249));  // 배경색 설정
            window.draw(pawSprite);     // 발바닥 이미지
            window.draw(startText);     // "고양이 발바닥 게임" 텍스트
            window.draw(startButton);   // Start 버튼
            window.draw(startButtonText);  // 버튼 텍스트
            window.display();    // 화면 업데이트
        }
        else if (gameState == GameState::Level) {
            // Level 화면에서 Easy 버튼 클릭 시 상태 변경
            if (startLevel(window, font) == "easy") {
                gameState = GameState::Easy;
            }
        }
        else if (gameState == GameState::Easy) {
            // Easy 화면 실행
            easyLevel(window, font);
        }
    }

    return 0;
}
