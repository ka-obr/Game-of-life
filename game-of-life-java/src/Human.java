import javax.swing.*;
import java.awt.*;

public class Human extends Animal {
    public static final ImageIcon humanIcon = new ImageIcon("images/human.png");

    public Human(World world) {
        super(5, 4, new Point(0, 0), world, 0); // Siła = 5, Inicjatywa = 4, pozycja (0,0)
    }

    public Human(Point location, World world, int age) {
        super(5, 4, location, world, age); // Siła = 5, Inicjatywa = 4
        this.position = location; // Ustawienie pozycji na podaną
        this.world = world; // Ustawienie świata
        this.age = age; // Ustawienie wieku
    }

    // Zmieniona metoda action(input) umożliwiająca poruszanie się człowieka i podejmowanie walki, jeśli pole jest zajęte
    @Override
    public void action(String input) {
        age++; // Inkrementacja wieku
        Point newPos = null;
        if (input.equalsIgnoreCase("up")) {
            newPos = new Point(position.x, position.y - 1);
        } else if (input.equalsIgnoreCase("down")) {
            newPos = new Point(position.x, position.y + 1);
        } else if (input.equalsIgnoreCase("left")) {
            newPos = new Point(position.x - 1, position.y);
        } else if (input.equalsIgnoreCase("right")) {
            newPos = new Point(position.x + 1, position.y);
        }
        if (newPos != null && 
            newPos.x >= 0 && newPos.y >= 0 && 
            newPos.x < world.getSize().x && newPos.y < world.getSize().y) {
            Organism occupant = world.getOrganismAtPosition(newPos);
            if (occupant != null) {
                // Jeśli pole jest zajęte, wywołujemy kolizję (human może zabić przeciwnika)
                collision(occupant);
            } else {
                position = newPos;
            }
        }
    }

    // Opcjonalnie: Jeśli action() bez parametrów ma pozostać, można go zdefiniować tak:
    @Override
    public void action() {
        age++; // Ruch bez podanego inputa nie jest wykonywany
    }

    @Override
    public ImageIcon getIcon() {
        return humanIcon;
    }
}
