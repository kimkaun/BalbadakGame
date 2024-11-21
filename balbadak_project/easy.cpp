#include <SFML/Graphics.hpp>
#include <cstdlib>  // 난수(정의된 범위 내에서 무작위로 추출한 수) 생성
#include <ctime>    // 현재 시간 
#include <vector>   // 동적 배열을 제공

void easyLevel(sf::RenderWindow& window, const sf::Font& font) {
    // 창 설정: 창 크기 및 색상 유지
    window.setSize(sf::Vector2u(800, 500));
    window.clear(sf::Color(222, 231, 249));

    // 점수 변수
    int score = 0;

    // 이미지 로드
    sf::Texture textures[3];
    if (!textures[0].loadFromFile("C:\\work\\c++_projects\\balbadak_project\\img\\imgb1.png") ||
        !textures[1].loadFromFile("C:\\work\\c++_projects\\balbadak_project\\img\\imgb2.png") ||
        !textures[2].loadFromFile("C:\\work\\c++_projects\\balbadak_project\\img\\imgb3.png")) {
        return; // 이미지 로드 실패 시 종료
    }

    // 점수 텍스트
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(50);
    scoreText.setFillColor(sf::Color(0, 0, 0));
    scoreText.setPosition(9, 10);

    // 타이머 텍스트 
    sf::Text timerText;
    timerText.setFont(font);
    timerText.setCharacterSize(50);
    timerText.setFillColor(sf::Color(0, 0, 0));
    timerText.setPosition(571, 16);

    // 난수 시드 설정
    std::srand(static_cast<unsigned int>(std::time(nullptr)));  // 현재 시간을 초 단위로 반환

    // 스프라이트 관리
    std::vector<sf::Sprite> sprites(3); // 객체를 3개 저장할 수 있는 동적배열을 생성
    const float targetWidth = 85.0f;
    const float targetHeight = 88.0f;

    // 각 스프라이트가 표시할 이미지를 연결
    for (int i = 0; i < 3; ++i) {
        sprites[i].setTexture(textures[i]);
        // 이미지의 원래 크기. 현재 크기 대비 목표 크기 비율
        float scaleX = targetWidth / sprites[i].getLocalBounds().width;
        float scaleY = targetHeight / sprites[i].getLocalBounds().height;
        sprites[i].setScale(scaleX, scaleY);
    }

    // 클릭된 스프라이트를 추적하기 위한 배열 (기본값은 false, 클릭된 경우 true)
    std::vector<bool> clicked(sprites.size(), false);

    // 시계 설정
    sf::Clock clock;
    float spawnInterval = 1.0f; // 1초 간격으로 이미지 변경
    sf::Clock timerClock;  // 게임 타이머용 시계

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // 마우스 버튼이 눌린 이벤트 감지. 눌린 버튼이 왼쪽 버튼인지 확인
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                // 2D 정수형 벡터 클래스 = 창 기준 마우스 위치 픽셀로 반환
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                for (size_t i = 0; i < sprites.size(); ++i) {
                    // 마우스 클릭이 해당 스프라이트의 경계 내에 있는지 확인
                    if (sprites[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        // 해당 스프라이트가 클릭되었으면
                        if (!clicked[i]) {  // 아직 클릭되지 않았다면
                            // 클릭된 이미지에 따라 점수 추가
                            if (i == 0) score += 5;         // imgb1 클릭 시 5점
                            else if (i == 1) score += 3;
                            else if (i == 2) score += 1;
                            clicked[i] = true;  // 클릭된 이미지로 표시
                        }
                    }
                }
            }

        }

        // 1초마다 이미지 3개를 무작위 위치에 배치 (spawnInterval : 이미지가 새로 나타나는 간격을 설정하는 변수
        if (clock.getElapsedTime().asSeconds() > spawnInterval) {
            // 각 스프라이트를 새 위치로 이동하기 전에 새로 나타난 이미지가 클릭되지 않은 상태로 초기화
            std::fill(clicked.begin(), clicked.end(), false);

            for (auto& sprite : sprites) {
                // 랜덤 위치 설정 (이미지가 화면을 벗어나지 않도록 제한)
                float x = static_cast<float>(std::rand() % (800 - static_cast<int>(targetWidth)));
                float y = static_cast<float>(std::rand() % (500 - static_cast<int>(targetHeight)));
                sprite.setPosition(x, y);
            }
            clock.restart(); // 타이머 리셋
        }

        // 점수 텍스트 업데이트
        scoreText.setString("score : " + std::to_string(score));

        // 타이머 업데이트 (초 단위)
        int elapsedTime = static_cast<int>(timerClock.getElapsedTime().asSeconds());
        timerText.setString("timer: " + std::to_string(30 - elapsedTime));

        // 타이머가 10초 이하일 때 색상 빨간색으로 변경
        if (30 - elapsedTime <= 10) {
            timerText.setFillColor(sf::Color::Red);
        }
        else {
            timerText.setFillColor(sf::Color(0, 0, 0)); // 기본 색상으로 설정
        }

        // 30초가 지나면 게임 클리어 실패
        if (elapsedTime >= 30) {
            sf::Text gameOverText;
            gameOverText.setFont(font);
            gameOverText.setCharacterSize(72);
            gameOverText.setFillColor(sf::Color(0, 0, 0));
            gameOverText.setString(L"저런... 다음에 또 도전하세요!");
            gameOverText.setPosition(90, 208);

            window.clear(sf::Color(222, 231, 249));  // 배경 색상
            window.draw(gameOverText);  // 게임 종료 텍스트 그리기
            window.display();
            sf::sleep(sf::seconds(3));  // 3초 후에 종료
            window.close();
            return;
        }
        // 100점이 넘으면 puplecat.cpp로 이동
        if (score >= 100) {
            

            system("start purplecat.cpp"); // purplecat.cpp를 실행
            return; // 종료
        }


        // 화면 지우기 및 그리기
        window.clear(sf::Color(222, 231, 249)); // 동일한 배경 색상
        window.draw(scoreText);  // 점수 텍스트 그리기
        window.draw(timerText);  // 타이머 텍스트 그리기
        for (const auto& sprite : sprites) {   // 모든 스프라이트 그리기
            window.draw(sprite);
        }
        window.display();
    }
}
