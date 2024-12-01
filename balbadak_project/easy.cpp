#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>  // SFML 오디오 관련 헤더 추가
#include <cstdlib>  // 난수(정의된 범위 내에서 무작위로 추출한 수) 생성
#include <ctime>    // 현재 시간 
#include <vector>   // 동적 배열을 제공

// easyLevel 함수 선언
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

    // 소리 초기화
    sf::Music bgm;
    if (!bgm.openFromFile("C:\\work\\c++_projects\\balbadak_project\\sound\\game_bgm.mp3")) return;
    bgm.setLoop(true);
    bgm.setVolume(40);  // 배경 음악 볼륨 설정
    bgm.play();

    // 실제 음원 데이터를 로드하고 저장
    sf::SoundBuffer clickBuffer, countdownBuffer, gameOverBuffer, gameWinBuffer; 
    if (!clickBuffer.loadFromFile("C:\\work\\c++_projects\\balbadak_project\\sound\\balbadak_tap.mp3") ||
        !countdownBuffer.loadFromFile("C:\\work\\c++_projects\\balbadak_project\\sound\\timer_second.mp3") ||
        !gameOverBuffer.loadFromFile("C:\\work\\c++_projects\\balbadak_project\\sound\\gameover.mp3") ||
        !gameWinBuffer.loadFromFile("C:\\work\\c++_projects\\balbadak_project\\sound\\game_win.mp3")) { 
        return;  // 소리 파일 중 하나라도 로드 실패 시 종료
    }

    sf::Sound clickSound(clickBuffer);      // 클릭 사운드 객체
    sf::Sound countdownSound(countdownBuffer);
    sf::Sound gameOverSound(gameOverBuffer);
    sf::Sound gameWinSound(gameWinBuffer);

    // 효과음 볼륨 설정
    clickSound.setVolume(50);       // 클릭 소리 볼륨 설정
    countdownSound.setVolume(70);   // 카운트다운 소리 볼륨 설정
    gameOverSound.setVolume(50);    // 게임 오버 소리 볼륨 설정
    gameWinSound.setVolume(50);     // 게임 승리 소리 볼륨

    // 시계 설정
    sf::Clock clock;
    float spawnInterval = 1.0f; // 1초 간격으로 이미지 변경(easy)
    sf::Clock timerClock;  // 게임 타이머용 시계

    bool countdownPlayed = false; // 10초 카운트다운 소리 재생 여부 확인

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
                            clickSound.play(); // 클릭 소리 재생
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
        timerText.setString("timer : " + std::to_string(30 - elapsedTime));

        // 30은 게임의 총 제한 시간 elapsedTime경과된 시간 
        if (30 - elapsedTime <= 10 && !countdownPlayed) {
            countdownSound.play();
            countdownPlayed = true; // 10초 소리 재생
        }

        // 타이머가 10초 이하일 때 색상 빨간색으로 변경
        if (30 - elapsedTime <= 10) {
            timerText.setFillColor(sf::Color::Red);
        }
        else {
            timerText.setFillColor(sf::Color(0, 0, 0)); // 기본 색상으로 설정
        }

        // 30초가 지나면 게임 클리어 실패
        if (elapsedTime >= 30) {
            bgm.stop(); // BGM 정지
            gameOverSound.play(); // 게임 실패 소리 재생

            // 게임 오버 텍스트 설정
            sf::Text gameOverText;
            gameOverText.setFont(font);
            gameOverText.setCharacterSize(72);
            gameOverText.setFillColor(sf::Color(0, 0, 0));
            gameOverText.setString(L"저런... 다음에 또 도전하세요!");
            gameOverText.setPosition(90, 208);

            // 화면 지우기 및 게임 오버 메시지 출력
            window.clear(sf::Color(222, 231, 249));  // 배경 색상
            window.draw(gameOverText);  // 게임 종료 텍스트 그리기
            window.display();

            sf::sleep(sf::seconds(5));  // 5초 후에 종료
            window.close();  // 창 닫기
            return;
        }

        // 100점이 넘으면 고양이 태어남
        if (score >= 100) {  
            bgm.stop(); // BGM 정지
            countdownSound.stop();  // 타이머 정지
            gameWinSound.play();    // 게임 성공 소리 재생

            // 알 이미지 로드
            sf::Texture eggTexture;
            if (!eggTexture.loadFromFile("C:\\work\\c++_projects\\balbadak_project\\img\\pupleegg.png")) {
                return;  // 이미지 로드 실패 시 종료
            }

            // 알 스프라이트
            sf::Sprite eggSprite;
            eggSprite.setTexture(eggTexture);
            float scaleX = 190.0f / eggSprite.getLocalBounds().width;
            float scaleY = 225.0f / eggSprite.getLocalBounds().height;
            eggSprite.setScale(scaleX, scaleY);
            eggSprite.setPosition(305, 182);  // 알 이미지 위치

            // 축하 텍스트 생성
            sf::Text congratulationText;
            congratulationText.setFont(font);
            congratulationText.setCharacterSize(60);
            congratulationText.setFillColor(sf::Color(153, 51, 255));
            congratulationText.setString(L"축하드려요! 이제 알을 눌러보세요!");
            congratulationText.setPosition(98, 70);

            // 텍스처 로드
            sf::Texture newTexture;
            if (!newTexture.loadFromFile("C:\\work\\c++_projects\\balbadak_project\\img\\puplecat.png")) {
                return;
            };
            sf::Sprite newSprite;
            newSprite.setTexture(newTexture);
            // 크기 조정: 텍스처가 설정된 이후에 getLocalBounds() 사용
            scaleX = 285.0f / newSprite.getLocalBounds().width;
            scaleY = 267.0f / newSprite.getLocalBounds().height;
            newSprite.setScale(scaleX, scaleY);
            newSprite.setPosition(257, 169);       // 고양이 이미지 위치

            // 알 클릭 후 바뀐 텍스트
            sf::Text newText;
            newText.setFont(font);
            newText.setCharacterSize(65);
            newText.setFillColor(sf::Color(0, 0, 0));
            newText.setString(L"고양이가 태어났어요!");
            newText.setPosition(192, 70);

            // 게임 성공 화면 초기화
            bool gameOver = false;
            bool eggClicked = false; // 알 이미지가 클릭되었는지 여부

            // 게임 루프
            while (window.isOpen() && !gameOver) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();  // 창 닫기
                        gameOver = true;
                    }

                    // 알 이미지 클릭 이벤트 처리
                    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);     // 현재 마우스의 위치를 가져옴 (화면에서)
                        // 마우스 클릭 위치가 범위에 있는지 확인
                        if (eggSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                            eggClicked = true;
                        }
                    }
                }

                // 화면 업데이트
                window.clear(sf::Color(222, 231, 249));  // 배경 색상 동일
                // 만약 알이 클릭되었다면
                if (eggClicked) {
                    window.draw(newText);    // 새로운 텍스트 그리기
                    window.draw(newSprite); // 새로운 이미지 그리기
                }
                else {
                    window.draw(congratulationText);  // 기존 텍스트 그리기
                    window.draw(eggSprite);          // 알 이미지 그리기
                }
                window.display();
            }
            return;  // 종료 후 함수 반환
        }

        // 화면 지우기 및 그리기
        window.clear(sf::Color(222, 231, 249)); 
        window.draw(scoreText);  
        window.draw(timerText); 
        for (const auto& sprite : sprites) {   // 모든 스프라이트 그리기
            window.draw(sprite);
        }
        window.display();
    }
}
