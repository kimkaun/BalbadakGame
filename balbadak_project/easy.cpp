#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>  // SFML ����� ���� ��� �߰�
#include <cstdlib>  // ����(���ǵ� ���� ������ �������� ������ ��) ����
#include <ctime>    // ���� �ð� 
#include <vector>   // ���� �迭�� ����

// easyLevel �Լ� ����
void easyLevel(sf::RenderWindow& window, const sf::Font& font) {

    // â ����: â ũ�� �� ���� ����
    window.setSize(sf::Vector2u(800, 500));
    window.clear(sf::Color(222, 231, 249));

    // ���� ����
    int score = 0;

    // �̹��� �ε�
    sf::Texture textures[3];
    if (!textures[0].loadFromFile("C:\\work\\c++_projects\\balbadak_project\\img\\imgb1.png") ||
        !textures[1].loadFromFile("C:\\work\\c++_projects\\balbadak_project\\img\\imgb2.png") ||
        !textures[2].loadFromFile("C:\\work\\c++_projects\\balbadak_project\\img\\imgb3.png")) {
        return; // �̹��� �ε� ���� �� ����
    }

    // ���� �ؽ�Ʈ
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(50);
    scoreText.setFillColor(sf::Color(0, 0, 0));
    scoreText.setPosition(9, 10);

    // Ÿ�̸� �ؽ�Ʈ 
    sf::Text timerText;
    timerText.setFont(font);
    timerText.setCharacterSize(50);
    timerText.setFillColor(sf::Color(0, 0, 0));
    timerText.setPosition(571, 16);

    // ���� �õ� ����
    std::srand(static_cast<unsigned int>(std::time(nullptr)));  // ���� �ð��� �� ������ ��ȯ

    // ��������Ʈ ����
    std::vector<sf::Sprite> sprites(3); // ��ü�� 3�� ������ �� �ִ� �����迭�� ����
    const float targetWidth = 85.0f;
    const float targetHeight = 88.0f;

    // �� ��������Ʈ�� ǥ���� �̹����� ����
    for (int i = 0; i < 3; ++i) {
        sprites[i].setTexture(textures[i]);
        // �̹����� ���� ũ��. ���� ũ�� ��� ��ǥ ũ�� ����
        float scaleX = targetWidth / sprites[i].getLocalBounds().width;
        float scaleY = targetHeight / sprites[i].getLocalBounds().height;
        sprites[i].setScale(scaleX, scaleY);
    }

    // Ŭ���� ��������Ʈ�� �����ϱ� ���� �迭 (�⺻���� false, Ŭ���� ��� true)
    std::vector<bool> clicked(sprites.size(), false);

    // �Ҹ� �ʱ�ȭ
    sf::Music bgm;
    if (!bgm.openFromFile("C:\\work\\c++_projects\\balbadak_project\\sound\\game_bgm.mp3")) return;
    bgm.setLoop(true);
    bgm.setVolume(40);  // ��� ���� ���� ����
    bgm.play();

    // ���� ���� �����͸� �ε��ϰ� ����
    sf::SoundBuffer clickBuffer, countdownBuffer, gameOverBuffer, gameWinBuffer; 
    if (!clickBuffer.loadFromFile("C:\\work\\c++_projects\\balbadak_project\\sound\\balbadak_tap.mp3") ||
        !countdownBuffer.loadFromFile("C:\\work\\c++_projects\\balbadak_project\\sound\\timer_second.mp3") ||
        !gameOverBuffer.loadFromFile("C:\\work\\c++_projects\\balbadak_project\\sound\\gameover.mp3") ||
        !gameWinBuffer.loadFromFile("C:\\work\\c++_projects\\balbadak_project\\sound\\game_win.mp3")) { 
        return;  // �Ҹ� ���� �� �ϳ��� �ε� ���� �� ����
    }

    sf::Sound clickSound(clickBuffer);      // Ŭ�� ���� ��ü
    sf::Sound countdownSound(countdownBuffer);
    sf::Sound gameOverSound(gameOverBuffer);
    sf::Sound gameWinSound(gameWinBuffer);

    // ȿ���� ���� ����
    clickSound.setVolume(50);       // Ŭ�� �Ҹ� ���� ����
    countdownSound.setVolume(70);   // ī��Ʈ�ٿ� �Ҹ� ���� ����
    gameOverSound.setVolume(50);    // ���� ���� �Ҹ� ���� ����
    gameWinSound.setVolume(50);     // ���� �¸� �Ҹ� ����

    // �ð� ����
    sf::Clock clock;
    float spawnInterval = 1.0f; // 1�� �������� �̹��� ����(easy)
    sf::Clock timerClock;  // ���� Ÿ�̸ӿ� �ð�

    bool countdownPlayed = false; // 10�� ī��Ʈ�ٿ� �Ҹ� ��� ���� Ȯ��

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // ���콺 ��ư�� ���� �̺�Ʈ ����. ���� ��ư�� ���� ��ư���� Ȯ��
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                // 2D ������ ���� Ŭ���� = â ���� ���콺 ��ġ �ȼ��� ��ȯ
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                for (size_t i = 0; i < sprites.size(); ++i) {
                    // ���콺 Ŭ���� �ش� ��������Ʈ�� ��� ���� �ִ��� Ȯ��
                    if (sprites[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        // �ش� ��������Ʈ�� Ŭ���Ǿ�����
                        if (!clicked[i]) {  // ���� Ŭ������ �ʾҴٸ�
                            // Ŭ���� �̹����� ���� ���� �߰�
                            if (i == 0) score += 5;         // imgb1 Ŭ�� �� 5��
                            else if (i == 1) score += 3;
                            else if (i == 2) score += 1;
                            clicked[i] = true;  // Ŭ���� �̹����� ǥ��
                            clickSound.play(); // Ŭ�� �Ҹ� ���
                        }
                    }
                }
            }

        }

        // 1�ʸ��� �̹��� 3���� ������ ��ġ�� ��ġ (spawnInterval : �̹����� ���� ��Ÿ���� ������ �����ϴ� ����
        if (clock.getElapsedTime().asSeconds() > spawnInterval) {
            // �� ��������Ʈ�� �� ��ġ�� �̵��ϱ� ���� ���� ��Ÿ�� �̹����� Ŭ������ ���� ���·� �ʱ�ȭ
            std::fill(clicked.begin(), clicked.end(), false);

            for (auto& sprite : sprites) {
                // ���� ��ġ ���� (�̹����� ȭ���� ����� �ʵ��� ����)
                float x = static_cast<float>(std::rand() % (800 - static_cast<int>(targetWidth)));
                float y = static_cast<float>(std::rand() % (500 - static_cast<int>(targetHeight)));
                sprite.setPosition(x, y);
            }
            clock.restart(); // Ÿ�̸� ����
        }

        // ���� �ؽ�Ʈ ������Ʈ
        scoreText.setString("score : " + std::to_string(score));
        // Ÿ�̸� ������Ʈ (�� ����)
        int elapsedTime = static_cast<int>(timerClock.getElapsedTime().asSeconds());
        timerText.setString("timer : " + std::to_string(30 - elapsedTime));

        // 30�� ������ �� ���� �ð� elapsedTime����� �ð� 
        if (30 - elapsedTime <= 10 && !countdownPlayed) {
            countdownSound.play();
            countdownPlayed = true; // 10�� �Ҹ� ���
        }

        // Ÿ�̸Ӱ� 10�� ������ �� ���� ���������� ����
        if (30 - elapsedTime <= 10) {
            timerText.setFillColor(sf::Color::Red);
        }
        else {
            timerText.setFillColor(sf::Color(0, 0, 0)); // �⺻ �������� ����
        }

        // 30�ʰ� ������ ���� Ŭ���� ����
        if (elapsedTime >= 30) {
            bgm.stop(); // BGM ����
            gameOverSound.play(); // ���� ���� �Ҹ� ���

            // ���� ���� �ؽ�Ʈ ����
            sf::Text gameOverText;
            gameOverText.setFont(font);
            gameOverText.setCharacterSize(72);
            gameOverText.setFillColor(sf::Color(0, 0, 0));
            gameOverText.setString(L"����... ������ �� �����ϼ���!");
            gameOverText.setPosition(90, 208);

            // ȭ�� ����� �� ���� ���� �޽��� ���
            window.clear(sf::Color(222, 231, 249));  // ��� ����
            window.draw(gameOverText);  // ���� ���� �ؽ�Ʈ �׸���
            window.display();

            sf::sleep(sf::seconds(5));  // 5�� �Ŀ� ����
            window.close();  // â �ݱ�
            return;
        }

        // 100���� ������ ����� �¾
        if (score >= 100) {  
            bgm.stop(); // BGM ����
            countdownSound.stop();  // Ÿ�̸� ����
            gameWinSound.play();    // ���� ���� �Ҹ� ���

            // �� �̹��� �ε�
            sf::Texture eggTexture;
            if (!eggTexture.loadFromFile("C:\\work\\c++_projects\\balbadak_project\\img\\pupleegg.png")) {
                return;  // �̹��� �ε� ���� �� ����
            }

            // �� ��������Ʈ
            sf::Sprite eggSprite;
            eggSprite.setTexture(eggTexture);
            float scaleX = 190.0f / eggSprite.getLocalBounds().width;
            float scaleY = 225.0f / eggSprite.getLocalBounds().height;
            eggSprite.setScale(scaleX, scaleY);
            eggSprite.setPosition(305, 182);  // �� �̹��� ��ġ

            // ���� �ؽ�Ʈ ����
            sf::Text congratulationText;
            congratulationText.setFont(font);
            congratulationText.setCharacterSize(60);
            congratulationText.setFillColor(sf::Color(153, 51, 255));
            congratulationText.setString(L"���ϵ����! ���� ���� ����������!");
            congratulationText.setPosition(98, 70);

            // �ؽ�ó �ε�
            sf::Texture newTexture;
            if (!newTexture.loadFromFile("C:\\work\\c++_projects\\balbadak_project\\img\\puplecat.png")) {
                return;
            };
            sf::Sprite newSprite;
            newSprite.setTexture(newTexture);
            // ũ�� ����: �ؽ�ó�� ������ ���Ŀ� getLocalBounds() ���
            scaleX = 285.0f / newSprite.getLocalBounds().width;
            scaleY = 267.0f / newSprite.getLocalBounds().height;
            newSprite.setScale(scaleX, scaleY);
            newSprite.setPosition(257, 169);       // ����� �̹��� ��ġ

            // �� Ŭ�� �� �ٲ� �ؽ�Ʈ
            sf::Text newText;
            newText.setFont(font);
            newText.setCharacterSize(65);
            newText.setFillColor(sf::Color(0, 0, 0));
            newText.setString(L"����̰� �¾���!");
            newText.setPosition(192, 70);

            // ���� ���� ȭ�� �ʱ�ȭ
            bool gameOver = false;
            bool eggClicked = false; // �� �̹����� Ŭ���Ǿ����� ����

            // ���� ����
            while (window.isOpen() && !gameOver) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();  // â �ݱ�
                        gameOver = true;
                    }

                    // �� �̹��� Ŭ�� �̺�Ʈ ó��
                    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);     // ���� ���콺�� ��ġ�� ������ (ȭ�鿡��)
                        // ���콺 Ŭ�� ��ġ�� ������ �ִ��� Ȯ��
                        if (eggSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                            eggClicked = true;
                        }
                    }
                }

                // ȭ�� ������Ʈ
                window.clear(sf::Color(222, 231, 249));  // ��� ���� ����
                // ���� ���� Ŭ���Ǿ��ٸ�
                if (eggClicked) {
                    window.draw(newText);    // ���ο� �ؽ�Ʈ �׸���
                    window.draw(newSprite); // ���ο� �̹��� �׸���
                }
                else {
                    window.draw(congratulationText);  // ���� �ؽ�Ʈ �׸���
                    window.draw(eggSprite);          // �� �̹��� �׸���
                }
                window.display();
            }
            return;  // ���� �� �Լ� ��ȯ
        }

        // ȭ�� ����� �� �׸���
        window.clear(sf::Color(222, 231, 249)); 
        window.draw(scoreText);  
        window.draw(timerText); 
        for (const auto& sprite : sprites) {   // ��� ��������Ʈ �׸���
            window.draw(sprite);
        }
        window.display();
    }
}
