#include <SFML/Graphics.hpp>
#include <cstdlib>  // ����(���ǵ� ���� ������ �������� ������ ��) ����
#include <ctime>    // ���� �ð� 
#include <vector>   // ���� �迭�� ����

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

    // �ð� ����
    sf::Clock clock;
    float spawnInterval = 1.0f; // 1�� �������� �̹��� ����
    sf::Clock timerClock;  // ���� Ÿ�̸ӿ� �ð�

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
        timerText.setString("timer: " + std::to_string(30 - elapsedTime));

        // Ÿ�̸Ӱ� 10�� ������ �� ���� ���������� ����
        if (30 - elapsedTime <= 10) {
            timerText.setFillColor(sf::Color::Red);
        }
        else {
            timerText.setFillColor(sf::Color(0, 0, 0)); // �⺻ �������� ����
        }

        // 30�ʰ� ������ ���� Ŭ���� ����
        if (elapsedTime >= 30) {
            sf::Text gameOverText;
            gameOverText.setFont(font);
            gameOverText.setCharacterSize(72);
            gameOverText.setFillColor(sf::Color(0, 0, 0));
            gameOverText.setString(L"����... ������ �� �����ϼ���!");
            gameOverText.setPosition(90, 208);

            window.clear(sf::Color(222, 231, 249));  // ��� ����
            window.draw(gameOverText);  // ���� ���� �ؽ�Ʈ �׸���
            window.display();
            sf::sleep(sf::seconds(3));  // 3�� �Ŀ� ����
            window.close();
            return;
        }
        // 100���� ������ puplecat.cpp�� �̵�
        if (score >= 100) {
            

            system("start purplecat.cpp"); // purplecat.cpp�� ����
            return; // ����
        }


        // ȭ�� ����� �� �׸���
        window.clear(sf::Color(222, 231, 249)); // ������ ��� ����
        window.draw(scoreText);  // ���� �ؽ�Ʈ �׸���
        window.draw(timerText);  // Ÿ�̸� �ؽ�Ʈ �׸���
        for (const auto& sprite : sprites) {   // ��� ��������Ʈ �׸���
            window.draw(sprite);
        }
        window.display();
    }
}
