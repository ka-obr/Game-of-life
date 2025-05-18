import javax.swing.*;
import java.awt.*;

public class Guarana extends Plant {
    private static final ImageIcon guaranaIcon = new ImageIcon("images/guarana.png");
    public static final Image scaledGuaranaIcon = guaranaIcon.getImage().getScaledInstance(30, 30, Image.SCALE_SMOOTH);

    public Guarana(Point position, World world, int age) {
        super(0, position, world, age);
    }

    @Override
    public ImageIcon getIcon() {
        return guaranaIcon;
    }

    @Override
    public void collision(Organism other) {
        other.setStrength(other.getStrength() + 3);
       String message = "Organism " + other.getClass().getSimpleName() + " consumed Guarana and gained +3 strength!";
       world.getWindow().addMessage(message);
    }
}
