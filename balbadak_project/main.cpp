#include <SFML/Graphics.hpp>
#include <locale>
#include "level.cpp"  // "level.cpp 클래스 포함
#include "easy.cpp"   // "easy.cpp" 
#include "normal.cpp" 
#include "hard.cpp"

// 열거형을 사용하여 게임의 상태를 관리
enum class GameState {
    Start,  
    Level,  
    Easy,
    Normal,
    Hard
};

int main() {
    // 한국어 지원
    std::locale::global(std::locale("ko_KR.UTF-8"));

    sf::RenderWindow window(sf::VideoMode(800, 500), "Cat Paw Tap Game");

    // 게임의 초기 상태를 Start로 설정
    GameState gameState = GameState::Start;

    // 폰트 로드
    sf::Font font;
    if (!font.loadFromFile("C:\\work\\c++_projects\\balbadak_project\\font\\ongelyp.ttf")) {
        return -1; // 폰트 로드 실패 시 프로그램 종료
    }

    // Start 화면 구성
    // 발바닥 스프라이트 설정
    sf::Texture pawTexture;
    sf::Sprite pawSprite;
    if (pawTexture.loadFromFile("C:\\work\\c++_projects\\balbadak_project\\img\\pink_balbadak.png")) {
        pawSprite.setTexture(pawTexture); // 텍스처를 스프라이트에 적용
        pawSprite.setPosition(98, 187);  
        // 스프라이트 크기를 원본 비율에 맞추어 조정
        pawSprite.setScale(85.0f / pawSprite.getLocalBounds().width,
            81.0f / pawSprite.getLocalBounds().height);
    }

    // Start 화면 제목
    sf::Text startText;
    startText.setFont(font);
    startText.setString(L"고양이 발바닥 게임"); 
    startText.setCharacterSize(96);           
    startText.setFillColor(sf::Color::Black); 
    startText.setPosition(140, 190);         

    // Start 버튼 사각형
    sf::RectangleShape startButton(sf::Vector2f(161, 55)); 
    startButton.setFillColor(sf::Color(134, 145, 244));    
    startButton.setPosition(320, 372);                   

    // Start 버튼 텍스트
    sf::Text startButtonText;
    startButtonText.setFont(font);
    startButtonText.setString(L"게임시작");
    startButtonText.setCharacterSize(55);     
    startButtonText.setFillColor(sf::Color::White); 
    startButtonText.setPosition(329, 362);  

    // 메인 게임 루프
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close(); // 창 닫기 이벤트 처리
            }

            // Start 화면 상태에서 Start 버튼 클릭 처리
            if (gameState == GameState::Start &&
                event.type == sf::Event::MouseButtonPressed &&
                startButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                gameState = GameState::Level; // 난이도 선택 화면으로 전환
            }
        }

        // Start 화면 그리기
        if (gameState == GameState::Start) {
            window.clear(sf::Color(222, 231, 249)); 
            window.draw(pawSprite);              
            window.draw(startText);                
            window.draw(startButton);             
            window.draw(startButtonText);         
            window.display();                     
        }

        // 난이도 선택 화면
        else if (gameState == GameState::Level) {   // 난이도 선택 화면
            // startLevel클래스의 객체를 생성
            startLevel levelScreen(window, font);
            std::string difficulty = levelScreen.run(); // run() 메서드가 선택된 난이도의 문자열을 반환 
            if (difficulty == "easy") {         // 반환된 문자열을 difficulty 변수에 저장
                gameState = GameState::Easy;    // Easy 난이도를 선택하면 Easy로 상태 변경
            }
            else if (difficulty == "normal") {  
                gameState = GameState::Normal;  
            }
            else if (difficulty == "hard") {    
                gameState = GameState::Hard;    
            }
        }
        // 각 난이도별 게임 실행
        else if (gameState == GameState::Easy) {
            easyLevel(window, font);  // Easy로 상태 변경하면 easyLevel함수 실행
        }
        else if (gameState == GameState::Normal) {
            normalLevel(window, font);  
        }
        else if (gameState == GameState::Hard) {
            hardLevel(window, font);   
        }
    }

    return 0; // 프로그램 종료
}
