#include <SFML/Graphics.hpp>
#include <string>

std::string startLevel(sf::RenderWindow& window, const sf::Font& font) {
    // 중앙에 표시할 텍스트 설정
    sf::Text text;
    text.setFont(font);
    text.setString(sf::String(L"난이도 선택"));
    text.setCharacterSize(64);
    text.setFillColor(sf::Color::Black);
    text.setPosition(303, 52);

    // 첫 번째 이미지 설정 (puppleegg.png)
    sf::Texture purpleEggTexture;
    sf::Sprite purpleEggSprite;
    if (purpleEggTexture.loadFromFile("C:\\work\\c++_projects\\balbadak_project\\img\\pupleegg.png")) {
        purpleEggSprite.setTexture(purpleEggTexture);
        purpleEggSprite.setPosition(77, 151);
        purpleEggSprite.setScale(190.0f / purpleEggSprite.getLocalBounds().width,  // getLocalBounds : 객체 자체의 크기를 반환
            225.0f / purpleEggSprite.getLocalBounds().height);                     // 원래의 스프라이트 크기를 유지한 채로, 원하는 크기로 조정가능
    }

    // 두 번째 이미지 설정 (yellowegg.png)
    sf::Texture yellowEggTexture;
    sf::Sprite yellowEggSprite;
    if (yellowEggTexture.loadFromFile("C:\\work\\c++_projects\\balbadak_project\\img\\yellowegg.png")) {
        yellowEggSprite.setTexture(yellowEggTexture);
        yellowEggSprite.setPosition(314, 151);
        yellowEggSprite.setScale(190.0f / yellowEggSprite.getLocalBounds().width,
            225.0f / yellowEggSprite.getLocalBounds().height);
    }

    // 세 번째 이미지 설정 (greenegg.png)
    sf::Texture greenEggTexture;
    sf::Sprite greenEggSprite;
    if (greenEggTexture.loadFromFile("C:\\work\\c++_projects\\balbadak_project\\img\\greenegg.png")) {
        greenEggSprite.setTexture(greenEggTexture);
        greenEggSprite.setPosition(551, 151);
        greenEggSprite.setScale(190.0f / greenEggSprite.getLocalBounds().width,
            225.0f / greenEggSprite.getLocalBounds().height);
    }

    // 버튼 텍스트 설정
    sf::Text buttonTextEasy;
    buttonTextEasy.setFont(font);
    buttonTextEasy.setString("easy");
    buttonTextEasy.setCharacterSize(64);
    buttonTextEasy.setFillColor(sf::Color(0x13, 0xB2, 0xE7));
    buttonTextEasy.setPosition(120, 376);

    sf::Text buttonTextNormal;
    buttonTextNormal.setFont(font);
    buttonTextNormal.setString("normal");
    buttonTextNormal.setCharacterSize(64);
    buttonTextNormal.setFillColor(sf::Color(0x13, 0xB2, 0xE7));
    buttonTextNormal.setPosition(336, 376);

    sf::Text buttonTextHard;
    buttonTextHard.setFont(font);
    buttonTextHard.setString("hard");
    buttonTextHard.setCharacterSize(64);
    buttonTextHard.setFillColor(sf::Color(0x13, 0xB2, 0xE7));
    buttonTextHard.setPosition(594, 376);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return "";
            }

            // Easy 버튼 클릭 감지
            if (event.type == sf::Event::MouseButtonPressed &&
                buttonTextEasy.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {   
                // mapPixelToCoords : 주어진 픽셀 좌표를 현재 뷰의 변환 상태를 고려해 월드 좌표(게임의 논리적 또는 가상 공간에서의 좌표)로 변환
                return "easy";
            }

            // Normal 버튼 클릭 감지
            if (event.type == sf::Event::MouseButtonPressed &&
                buttonTextNormal.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                return "normal";
            }

            // Hard 버튼 클릭 감지
            if (event.type == sf::Event::MouseButtonPressed &&
                buttonTextHard.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                return "hard";
            }
        }

        // 화면 지우기 및 그리기
        window.clear(sf::Color(222, 231, 249));
        window.draw(text);             // 텍스트 그리기
        window.draw(purpleEggSprite);  // 첫 번째 알 이미지
        window.draw(yellowEggSprite);  // 두 번째 알 이미지
        window.draw(greenEggSprite);   // 세 번째 알 이미지
        window.draw(buttonTextEasy);   // easy 버튼 텍스트
        window.draw(buttonTextNormal); // normal 버튼 텍스트
        window.draw(buttonTextHard);   // hard 버튼 텍스트
        window.display();
    }

    return "";
}
