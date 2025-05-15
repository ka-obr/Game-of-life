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
    private JTextArea messageArea; // Panel wiadomości

    public Window(Gameplay gameplay) {
        this.world = gameplay.getWorld();

        // Obliczanie rozmiaru okna na podstawie rozmiaru siatki
        Size gridSize = world.getSize();
        int windowWidth = gridSize.x * TILE_SIZE + 300; // Dodanie miejsca na panel wiadomości
        int windowHeight = gridSize.y * TILE_SIZE + 200; // Dodanie marginesu na pasek tytułu

        setTitle("Karol Obrycki 203264");
        setSize(windowWidth, windowHeight);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        // Tworzenie głównego układu
        setLayout(new BorderLayout());

        // Panel rysowania
        drawingPanel = new DrawingPanel();
        add(drawingPanel, BorderLayout.CENTER);

        // Panel wiadomości
        messageArea = new JTextArea();
        messageArea.setEditable(false);
        messageArea.setLineWrap(true);
        messageArea.setWrapStyleWord(true);
        messageArea.setBackground(new Color(46, 90, 46)); // Ciemnozielone tło
        messageArea.setForeground(Color.WHITE); // Biały tekst
        messageArea.setFont(new Font("Arial", Font.BOLD, 20)); // Zwiększona czcionka

        JScrollPane scrollPane = new JScrollPane(messageArea);
        scrollPane.setPreferredSize(new Dimension(400, getHeight())); // Zwiększona szerokość panelu wiadomości
        add(scrollPane, BorderLayout.EAST);

        // Ustawienie okna jako focusable, aby odbierało zdarzenia klawiatury
        setFocusable(true);
        requestFocusInWindow();

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
                        dispose(); // Zamknięcie głównego okna
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

    public void addMessage(String message) {
        messageArea.append(message + "\n");
        messageArea.setCaretPosition(messageArea.getDocument().getLength()); // Automatyczne przewijanie do końca
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
        int centerX = (getWidth() - gridWidth) / 2 - 200; //FIX
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

    private <T extends Plant> void addPlantOption(JPopupMenu popupMenu, Class<T> plantClass, ImageIcon icon, Point tilePosition) {
        JMenuItem menuItem = new JMenuItem(icon);
        menuItem.setOpaque(false);
        menuItem.setBorder(BorderFactory.createEmptyBorder());
        menuItem.addActionListener(e -> {
            try {
                T plant = plantClass.getConstructor(Point.class, World.class, int.class)
                        .newInstance(tilePosition, world, 1);
                world.addOrganism(plant);
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

        closeActivePopupMenu();

        JPopupMenu categoryMenu = createCategoryMenu(tileX, tileY);
        showPopupMenu(categoryMenu, tileX, tileY);
    }

    private JPopupMenu createCategoryMenu(int tileX, int tileY) {
        JPopupMenu categoryMenu = new JPopupMenu();
        activePopupMenu = categoryMenu;

        JMenuItem animalOption = new JMenuItem("Animal");
        animalOption.addActionListener(e -> {
            categoryMenu.setVisible(false);
            showAnimalAddMenu(tileX, tileY);
        });
        categoryMenu.add(animalOption);

        JMenuItem plantOption = new JMenuItem("Plant");
        plantOption.addActionListener(e -> {
            categoryMenu.setVisible(false);
            showPlantAddMenu(tileX, tileY);
        });
        categoryMenu.add(plantOption);

        return categoryMenu;
    }

    private void showAnimalAddMenu(int tileX, int tileY) {
        Point tilePosition = new Point(tileX, tileY);
        JPopupMenu animalMenu = createAnimalMenu(tilePosition);
        showPopupMenu(animalMenu, tileX, tileY);
    }

    private void showPlantAddMenu(int tileX, int tileY) {
        Point tilePosition = new Point(tileX, tileY);
        JPopupMenu plantMenu = createPlantMenu(tilePosition);
        showPopupMenu(plantMenu, tileX, tileY);
    }

    private JPopupMenu createAnimalMenu(Point tilePosition) {
        JPopupMenu animalMenu = new JPopupMenu();
        activePopupMenu = animalMenu;

        addAnimalOption(animalMenu, Sheep.class, new ImageIcon(Sheep.scaledSheepIcon), tilePosition);
        addAnimalOption(animalMenu, Wolf.class, new ImageIcon(Wolf.scaledWolfIcon), tilePosition);
        addAnimalOption(animalMenu, Fox.class, new ImageIcon(Fox.scaledFoxIcon), tilePosition);
        addAnimalOption(animalMenu, Turtle.class, new ImageIcon(Turtle.scaledTurtleIcon), tilePosition);
        addAnimalOption(animalMenu, Antelope.class, new ImageIcon(Antelope.scaledAntelopeIcon), tilePosition);

        return animalMenu;
    }

    private JPopupMenu createPlantMenu(Point tilePosition) {
        JPopupMenu plantMenu = new JPopupMenu();
        activePopupMenu = plantMenu;

        addPlantOption(plantMenu, Grass.class, new ImageIcon(Grass.scaledGrassIcon), tilePosition);
        addPlantOption(plantMenu, Dandelion.class, new ImageIcon(Dandelion.scaledDandelionIcon), tilePosition);
        addPlantOption(plantMenu, Guarana.class, new ImageIcon(Guarana.scaledGuaranaIcon), tilePosition);

        return plantMenu;
    }

    private void showPopupMenu(JPopupMenu menu, int tileX, int tileY) {
        int tileWidth = TILE_SIZE, tileHeight = TILE_SIZE;
        int gridWidth = world.getSize().x * tileWidth;
        int gridHeight = world.getSize().y * tileHeight;
        int panelCenterX = (drawingPanel.getWidth() - gridWidth) / 2;
        int panelCenterY = (drawingPanel.getHeight() - gridHeight) / 2;
        int tileCenterX = offsetX + panelCenterX + tileX * tileWidth + tileWidth / 2;
        int tileCenterY = offsetY + panelCenterY + tileY * tileHeight + tileHeight / 2;
        Dimension popupSize = menu.getPreferredSize();
        int popupX = tileCenterX - popupSize.width / 2;
        int popupY = tileCenterY - popupSize.height / 2;
        menu.show(drawingPanel, popupX, popupY);
    }

    private void closeActivePopupMenu() {
        if (activePopupMenu != null) {
            activePopupMenu.setVisible(false);
            activePopupMenu = null;
            drawingPanel.repaint();
        }
    }
}
