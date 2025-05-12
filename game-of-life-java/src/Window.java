import lib.Size;
import javax.swing.*;
import java.awt.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionAdapter;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Window extends JFrame {
    private static final int TILE_SIZE = 50; // Stały rozmiar kafelka
    private World world;
    private int offsetX = 0, offsetY = 0; // Przesunięcie mapy
    private Point dragStart = null; // Punkt początkowy przeciągania
    private JPopupMenu activePopupMenu = null; // Przechowuje aktualnie otwarte menu
    private DrawingPanel drawingPanel; // Panel rysowania

    public Window(Gameplay gameplay) {
        this.world = gameplay.getWorld(); // Przypisanie świata

        // Obliczanie rozmiaru okna na podstawie rozmiaru siatki
        Size gridSize = world.getSize();
        int windowWidth = gridSize.x * TILE_SIZE + 200; // Dodanie marginesu na ramkę
        int windowHeight = gridSize.y * TILE_SIZE + 200; // Dodanie marginesu na pasek tytułu

        setTitle("Game of Life");
        setSize(windowWidth, windowHeight);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        drawingPanel = new DrawingPanel();
        add(drawingPanel);

        addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e) {
                String input = null;
                switch (e.getKeyCode()) {
                    case KeyEvent.VK_UP:
                        input = "up";
                        break;
                    case KeyEvent.VK_DOWN:
                        input = "down";
                        break;
                    case KeyEvent.VK_LEFT:
                        input = "left";
                        break;
                    case KeyEvent.VK_RIGHT:
                        input = "right";
                        break;
                    case KeyEvent.VK_Q:
                        input = "q";
                        break;
                    default:
                        input = String.valueOf(e.getKeyChar());
                }
                gameplay.handleInput(input);
                drawingPanel.repaint(); // Odświeżenie panelu rysowania
            }
        });

        addMouseListener(new MouseAdapter() {
            @Override
            public void mousePressed(MouseEvent e) {
                if (SwingUtilities.isRightMouseButton(e)) {
                    dragStart = e.getPoint(); // Zapisanie punktu początkowego przeciągania
                } else if (SwingUtilities.isLeftMouseButton(e)) {
                    handleTileClick(e.getPoint()); // Obsługa kliknięcia lewym przyciskiem myszy
                }
            }

            @Override
            public void mouseReleased(MouseEvent e) {
                if (SwingUtilities.isRightMouseButton(e)) {
                    dragStart = null; // Zakończenie przeciągania
                }
            }
        });

        addMouseMotionListener(new MouseMotionAdapter() {
            @Override
            public void mouseDragged(MouseEvent e) {
                if (dragStart != null && SwingUtilities.isRightMouseButton(e)) {
                    int dx = e.getX() - dragStart.x;
                    int dy = e.getY() - dragStart.y;
                    offsetX += dx;
                    offsetY += dy;
                    dragStart = e.getPoint(); // Aktualizacja punktu początkowego
                    drawingPanel.repaint(); // Odświeżenie panelu rysowania
                }
            }
        });

        setVisible(true);
    }

    private class DrawingPanel extends JPanel {
        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);

            // Ustawienie koloru tła na ciemnozielony
            g.setColor(new Color(46, 90, 46)); // Ciemnozielony
            g.fillRect(0, 0, getWidth(), getHeight());

            drawWorld(g);
        }

        private void drawWorld(Graphics g) {
            Graphics2D g2d = (Graphics2D) g;

            // Obliczanie przesunięcia, aby siatka była wyśrodkowana
            Size size = world.getSize();
            int gridWidth = size.x * TILE_SIZE;
            int gridHeight = size.y * TILE_SIZE;

            int centerX = (getWidth() - gridWidth) / 2;
            int centerY = (getHeight() - gridHeight) / 2;

            g2d.translate(offsetX + centerX, offsetY + centerY); // Przesunięcie mapy i wyśrodkowanie

            // Rysowanie siatki
            for (int i = 0; i < size.x; i++) {
                for (int j = 0; j < size.y; j++) {
                    g2d.setColor(new Color(67, 131, 67)); // Jasnozielony
                    g2d.fillRect(i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE); // Wypełnienie kafelka

                    g2d.setColor(new Color(46, 90, 46)); // Ciemnozielony kolor dla obramowania
                    g2d.setStroke(new BasicStroke(3)); // Ustawienie grubości linii na 3 piksele
                    g2d.drawRect(i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE); // Rysowanie obramowania kafelka
                }
            }

            // Rysowanie organizmów
            for (Organism organism : world.getOrganisms()) {
                Point position = organism.getPosition();
                ImageIcon icon = organism.getIcon();

                if (icon != null) {
                    Image image = icon.getImage();
                    int imageWidth = (int) (TILE_SIZE * 0.8);
                    int imageHeight = (int) (TILE_SIZE * 0.8);

                    // Centrowanie obrazu w kafelku z lekkim przesunięciem w dół
                    int xOffset = (TILE_SIZE - imageWidth) / 2;
                    int yOffset = (TILE_SIZE - imageHeight) / 2 + 1;

                    g2d.drawImage(image, position.x * TILE_SIZE + xOffset, position.y * TILE_SIZE + yOffset, imageWidth, imageHeight, this);
                }
            }
        }
    }

    private void handleTileClick(Point clickPoint) {
        Size size = world.getSize();
        int tileWidth = 50;
        int tileHeight = 50;

        // Obliczanie przesunięcia, aby siatka była wyśrodkowana
        int gridWidth = size.x * tileWidth;
        int gridHeight = size.y * tileHeight;
        int centerX = (getWidth() - gridWidth) / 2;
        int centerY = (getHeight() - gridHeight) / 2;

        int adjustedX = clickPoint.x - offsetX - centerX;
        int adjustedY = clickPoint.y - offsetY - centerY;

        int tileX = adjustedX / tileWidth;
        int tileY = adjustedY / tileHeight;

        if (tileX >= 0 && tileX < size.x && tileY >= 0 && tileY < size.y) {
            showAddMenu(tileX, tileY);
        }
    }

    private <T extends Animal> void addAnimalOption(JPopupMenu popupMenu, Class<T> animalClass, ImageIcon icon, Point tilePosition) {
        JMenuItem menuItem = new JMenuItem(icon);
        menuItem.setOpaque(false);
        menuItem.setBorder(BorderFactory.createEmptyBorder());
        menuItem.addActionListener(e -> {
            try {
                T animal = animalClass.getConstructor(Point.class, World.class, int.class)
                        .newInstance(tilePosition, world, 1);
                world.addOrganism(animal);
                drawingPanel.repaint();
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        });
        popupMenu.add(menuItem);
    }

    private void showAddMenu(int tileX, int tileY) {
        Point tilePosition = new Point(tileX, tileY);
        if (world.isTileOccupied(tilePosition)) {
            return; // Nie pokazuj menu, jeśli kafelek jest zajęty
        }

        // Zamknięcie poprzedniego menu, jeśli istnieje
        if (activePopupMenu != null) {
            activePopupMenu.setVisible(false);
            activePopupMenu = null;
            drawingPanel.repaint();
        }

        JPopupMenu popupMenu = new JPopupMenu();
        activePopupMenu = popupMenu;

        // Opcja dodania owcy
        addAnimalOption(popupMenu, Sheep.class, new ImageIcon(Sheep.scaledSheepIcon), tilePosition);
        addAnimalOption(popupMenu, Wolf.class, new ImageIcon(Wolf.scaledWolfIcon), tilePosition);

        int tileWidth = 50;
        int tileHeight = 50;
        int gridWidth = world.getSize().x * tileWidth;
        int gridHeight = world.getSize().y * tileHeight;
        // Używamy wymiarów panelu rysowania do wyśrodkowania siatki
        int panelCenterX = (drawingPanel.getWidth() - gridWidth) / 2;
        int panelCenterY = (drawingPanel.getHeight() - gridHeight) / 2;

        // Obliczamy środek klikniętego kafelka
        int tileCenterX = offsetX + panelCenterX + tileX * tileWidth + tileWidth / 2;
        int tileCenterY = offsetY + panelCenterY + tileY * tileHeight + tileHeight / 2;
        Dimension popupSize = popupMenu.getPreferredSize();
        int popupX = tileCenterX - popupSize.width / 2;
        int popupY = tileCenterY - popupSize.height / 2;
        popupMenu.show(drawingPanel, popupX, popupY);
    }
}
