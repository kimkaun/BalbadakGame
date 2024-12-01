#include <SFML/Graphics.hpp>
#include <string>

// 난이도 선택 화면을 구현하는 클래스
class startLevel {
// 클래스 내부에서만 사용하는 데이터 보호
private:
    sf::RenderWindow& window;    // window 객체 참조
    sf::Font font;               
    sf::Text titleText;          
    sf::Text buttonTextEasy;    
    sf::Text buttonTextNormal;   
    sf::Text buttonTextHard;    
    sf::Sprite purpleEggSprite;  
    sf::Sprite yellowEggSprite;  
    sf::Sprite greenEggSprite;   
    sf::Texture purpleEggTexture; 
    sf::Texture yellowEggTexture; 
    sf::Texture greenEggTexture;  

    // 난이도 선택 화면 초기화 함수
    void initialize() {
        // 제목 텍스트 설정
        titleText.setFont(font);                        
        titleText.setString(sf::String(L"난이도 선택")); 
        titleText.setCharacterSize(64);                
        titleText.setFillColor(sf::Color::Black);      
        titleText.setPosition(303, 52);               

        // Easy 버튼 이미지 설정
        if (purpleEggTexture.loadFromFile("C:\\work\\c++_projects\\balbadak_project\\img\\pupleegg.png")) {
            purpleEggSprite.setTexture(purpleEggTexture); 
            purpleEggSprite.setPosition(77, 151);      
            purpleEggSprite.setScale(190.0f / purpleEggSprite.getLocalBounds().width,
                225.0f / purpleEggSprite.getLocalBounds().height); // 크기
        }

        // Normal 버튼 이미지 설정
        if (yellowEggTexture.loadFromFile("C:\\work\\c++_projects\\balbadak_project\\img\\yellowegg.png")) {
            yellowEggSprite.setTexture(yellowEggTexture);
            yellowEggSprite.setPosition(314, 151);
            yellowEggSprite.setScale(190.0f / yellowEggSprite.getLocalBounds().width,
                225.0f / yellowEggSprite.getLocalBounds().height);
        }

        // Hard 버튼 이미지 설정
        if (greenEggTexture.loadFromFile("C:\\work\\c++_projects\\balbadak_project\\img\\greenegg.png")) {
            greenEggSprite.setTexture(greenEggTexture);
            greenEggSprite.setPosition(551, 151);
            greenEggSprite.setScale(190.0f / greenEggSprite.getLocalBounds().width,
                225.0f / greenEggSprite.getLocalBounds().height);
        }

        // Easy 버튼 텍스트 
        buttonTextEasy.setFont(font);
        buttonTextEasy.setString("easy");              
        buttonTextEasy.setCharacterSize(64);            
        buttonTextEasy.setFillColor(sf::Color(19, 178, 231)); 
        buttonTextEasy.setPosition(120, 376);          

        // Normal 버튼 텍스트 
        buttonTextNormal.setFont(font);
        buttonTextNormal.setString("normal");
        buttonTextNormal.setCharacterSize(64);
        buttonTextNormal.setFillColor(sf::Color(19, 178, 231));
        buttonTextNormal.setPosition(336, 376);

        // Hard 버튼 텍스트 
        buttonTextHard.setFont(font);
        buttonTextHard.setString("hard");
        buttonTextHard.setCharacterSize(64);
        buttonTextHard.setFillColor(sf::Color(19, 178, 231));
        buttonTextHard.setPosition(594, 376);
    }

public:
    // 생성자: 창과 폰트를 받아 초기화
    startLevel(sf::RenderWindow& win, const sf::Font& f)
        : window(win), font(f) {
        initialize(); // 초기화 함수 호출
    }

    // 난이도 선택 화면 실행
    std::string run() {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close(); // 창이 닫히면 프로그램 종료
                    return "";      // 빈 문자열 반환
                }

                // Easy 버튼 클릭 감지
                if (event.type == sf::Event::MouseButtonPressed &&
                    buttonTextEasy.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    // mapPixelToCoords : 주어진 픽셀 좌표를 현재 뷰의 변환 상태를 고려해 월드 좌표(게임의 논리적 또는 가상 공간에서의 좌표)로 변환
                    return "easy";  // Easy 난이도 선택 시 "easy" 반환
                }

                // Normal 버튼 클릭 감지
                if (event.type == sf::Event::MouseButtonPressed &&
                    buttonTextNormal.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    return "normal"; // Normal 난이도 선택 시 "normal" 반환
                }

                // Hard 버튼 클릭 감지
                if (event.type == sf::Event::MouseButtonPressed &&
                    buttonTextHard.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    return "hard";  // Hard 난이도 선택 시 "hard" 반환
                }
            }

            // 화면을 지우고 새로 그리기
            window.clear(sf::Color(222, 231, 249)); 
            window.draw(titleText);               
            window.draw(purpleEggSprite);          
            window.draw(yellowEggSprite);         
            window.draw(greenEggSprite);           
            window.draw(buttonTextEasy);           
            window.draw(buttonTextNormal);         
            window.draw(buttonTextHard);          
            window.display();                    
        }

        return ""; // 창이 닫히거나 이벤트 루프가 종료되면 빈 문자열 반환
    }
};
