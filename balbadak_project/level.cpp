#include <SFML/Graphics.hpp>
#include <string>

std::string startLevel(sf::RenderWindow& window, const sf::Font& font) {
    // �߾ӿ� ǥ���� �ؽ�Ʈ ����
    sf::Text text;
    text.setFont(font);
    text.setString(sf::String(L"���̵� ����"));
    text.setCharacterSize(64);
    text.setFillColor(sf::Color::Black);
    text.setPosition(303, 52);

    // ù ��° �̹��� ���� (puppleegg.png)
    sf::Texture purpleEggTexture;
    sf::Sprite purpleEggSprite;
    if (purpleEggTexture.loadFromFile("C:\\work\\c++_projects\\balbadak_project\\img\\pupleegg.png")) {
        purpleEggSprite.setTexture(purpleEggTexture);
        purpleEggSprite.setPosition(77, 151);
        purpleEggSprite.setScale(190.0f / purpleEggSprite.getLocalBounds().width,  // getLocalBounds : ��ü ��ü�� ũ�⸦ ��ȯ
            225.0f / purpleEggSprite.getLocalBounds().height);                     // ������ ��������Ʈ ũ�⸦ ������ ä��, ���ϴ� ũ��� ��������
    }

    // �� ��° �̹��� ���� (yellowegg.png)
    sf::Texture yellowEggTexture;
    sf::Sprite yellowEggSprite;
    if (yellowEggTexture.loadFromFile("C:\\work\\c++_projects\\balbadak_project\\img\\yellowegg.png")) {
        yellowEggSprite.setTexture(yellowEggTexture);
        yellowEggSprite.setPosition(314, 151);
        yellowEggSprite.setScale(190.0f / yellowEggSprite.getLocalBounds().width,
            225.0f / yellowEggSprite.getLocalBounds().height);
    }

    // �� ��° �̹��� ���� (greenegg.png)
    sf::Texture greenEggTexture;
    sf::Sprite greenEggSprite;
    if (greenEggTexture.loadFromFile("C:\\work\\c++_projects\\balbadak_project\\img\\greenegg.png")) {
        greenEggSprite.setTexture(greenEggTexture);
        greenEggSprite.setPosition(551, 151);
        greenEggSprite.setScale(190.0f / greenEggSprite.getLocalBounds().width,
            225.0f / greenEggSprite.getLocalBounds().height);
    }

    // ��ư �ؽ�Ʈ ����
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

            // Easy ��ư Ŭ�� ����
            if (event.type == sf::Event::MouseButtonPressed &&
                buttonTextEasy.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {   
                // mapPixelToCoords : �־��� �ȼ� ��ǥ�� ���� ���� ��ȯ ���¸� ����� ���� ��ǥ(������ ���� �Ǵ� ���� ���������� ��ǥ)�� ��ȯ
                return "easy";
            }

            // Normal ��ư Ŭ�� ����
            if (event.type == sf::Event::MouseButtonPressed &&
                buttonTextNormal.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                return "normal";
            }

            // Hard ��ư Ŭ�� ����
            if (event.type == sf::Event::MouseButtonPressed &&
                buttonTextHard.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                return "hard";
            }
        }

        // ȭ�� ����� �� �׸���
        window.clear(sf::Color(222, 231, 249));
        window.draw(text);             // �ؽ�Ʈ �׸���
        window.draw(purpleEggSprite);  // ù ��° �� �̹���
        window.draw(yellowEggSprite);  // �� ��° �� �̹���
        window.draw(greenEggSprite);   // �� ��° �� �̹���
        window.draw(buttonTextEasy);   // easy ��ư �ؽ�Ʈ
        window.draw(buttonTextNormal); // normal ��ư �ؽ�Ʈ
        window.draw(buttonTextHard);   // hard ��ư �ؽ�Ʈ
        window.display();
    }

    return "";
}
