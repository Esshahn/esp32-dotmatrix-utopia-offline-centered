/*
 * Framed Utopia - ESP32 LED Matrix Display
 * 
 * Button Controls:
 * - On first boot, enters time setup mode
 * - During time setup:
 *   * Short press: Increment hour (0-23)
 *   * Long press (2 seconds): Confirm time and exit setup
 * - After time is set:
 *   * Device runs automatically, no button interaction needed
 *   * Time advances internally, no RTC required
 *   * Device sleeps between SLEEP_HOUR (22:00) and WAKE_HOUR (07:00)
 */

// only seems to work with the ESP32 by espressiv 2.x platform, not the 3.x

#include "ESP32-HUB75-MatrixPanel-I2S-DMA.h"

// Messages array
const char* const utopias[] = {
    "Ewiger Sommer, niemals zu heiss",
    "Laechelnde Baeume, sprechende Blumen",
    "Kaffee regnet in der Frueh",
    "Zeitreisen fuer alle",
    "Katzen verstehen Menschen",
    "Instant-Heilung durch Umarmungen",
    "Pizza ist gesund",
    "Fliegen ohne Flugzeug",
    "Weltfrieden, garantiert",
    "Hologramm-Haustiere",
    "Null Verkehrsstaus",
    "Gedanken teilen per Blick",
    "Roboter erledigen Hausarbeit",
    "Laecheln verlaengert das Leben",
    "Jeder ist Kuenstler",
    "Allwissende Bibliotheken fuer alle",
    "Hunde koennen fliegen",
    "Tanzen macht unsichtbar",
    "Gesunde Schokolade",
    "Singende Regenschirme",
    "Telepathische Pizza-Bestellung",
    "Glueckskekse erraten die Zukunft",
    "Selbstreinigende Kleidung",
    "Alle Sprachen verstehen",
    "Musik in der Luft",
    "Lachen als Waehrung",
    "Schwerkraft auf Wunsch",
    "Gedankenkontrollierte TV-Fernbedienung",
    "Umweltfreundliche Unicorn-Farmen",
    "Kuschel-Roboter als Therapeuten",
    "Essen, das nie kalt wird",
    "Inseln aus Schokolade",
    "Sofas, die sich anpassen",
    "Pflanzen tanzen bei Sonnenuntergang",
    "Teleportation zum Mond",
    "Glueckliche Wolken",
    "Wasserrutschen im Buero",
    "Vergesslichkeit heilt Schmerzen",
    "Kleidung aendert sich nach Laune",
    "Musikinstrumente spielen sich selbst",
    "Kinder erklaeren die Welt",
    "Laechelnde Verkehrsschilder",
    "Null Kalorien in Wochenenden",
    "Tiere sprechen Englisch",
    "Sonnenbrillen fuer Traeume",
    "Kaffee bringt Weltfrieden",
    "Yoga macht unverwundbar",
    "Trampolinfloors im Buero",
    "Telepathische Umarmungen",
    "Schwimmende Bibliotheken",
    "Quantencomputer fuer alle",
    "Regen aus Schokolade",
    "Spontane Tanzpartys weltweit",
    "Bienen sprechen Esperanto",
    "Jeder Tag ist ein Feiertag",
    "Schokolade senkt den Blutdruck",
    "Frieden durch gemeinsames Kochen",
    "Insekten als Haustiere",
    "Roboter als beste Freunde",
    "Sport macht schlau",
    "Teleportation statt Pendeln",
    "Umweltfreundliche Flugautos",
    "Ehrliche Politiker",
    "Roboter-Katzen-Kombinationen",
    "Sprachunterricht durch Schlafen",
    "Freie Energie aus Lachen",
    "Inseln schweben in der Luft",
    "Trampolinfloors im Supermarkt",
    "Tanzende Sterne bei Nacht",
    "Schokolade, die Gewicht verliert",
    "Virtuelle Realitaet im Schlaf",
    "Fliegende Fahrraeder",
    "Gute Nachrichten als Standard",
    "Friedliche Roboterrevolution",
    "Musik in jedem Regentropfen",
    "Wissenschaft als Unterhaltung",
    "Fliegende Haeuser",
    "Unterwasserstaedte",
    "Roboter als Kuenstler",
    "Unsichtbare Bibliotheken",
    "Klimaanlagen durch Lachen",
    "Selbstputzende Fenster",
    "Essen waechst in jeder Ecke",
    "Mond als Ferienziel",
    "Farbwechselnde Haare",
    "Autos, die Geschichten erzaehlen",
    "Unendliche Erdbeeren",
    "Alle sind Nachbarn",
    "Roboter als Lehrer",
    "Glueck ist ansteckend",
    "Wasser als Sprudelgetraenk",
    "Freundschaft heilt alle Wunden",
    "Buecher, die Gedanken lesen",
    "Regenbogenstrassen statt Grau",
    "Schokolade macht schlau",
    "Reisen ohne Koffer packen",
    "Gedankenblitze im Sonnenuntergang",
    "Wolken als weiche Betten",
    "Lichtgeschwindigkeit zum Fruehstueck",
    "Roboter als geniale Koeche",
    "Tiere sprechen Poetry-Slam",
    "Kaffee trinken auf dem Mond",
    "Umweltfreundliche Jetpacks fuer alle",
    "Unendliche Erdbeermarmelade",
    "Riesentrampolinfloors weltweit",
    "Hologramm-Konzerte im Wohnzimmer",
    "Fliegende Eiscreme-Lieferanten",
    "Tanzende Northern Lights",
    "Sprache der Liebe im Radio",
    "Kostenlose Energie aus Lachen",
    "Kuschelnde Roboter als Therapeuten",
    "Magische Bruecken zu jeder Insel",
    "Telepathie als universelle Sprache",
    "Farbwechselnde Haare im Wind",
    "Automatische Gute-Laune-Musik",
    "Unsichtbare Taschen mit allem",
    "Baeume, die Geschichten erzaehlen",
    "Selbstheilende Blumenbeete",
    "Kaffeeplantagen auf jedem Balkon",
    "Gesunde Schokolade als Fruehstueck",
    "Klimaanlagen durch Lachen in Bueros",
    "Reiseziele auf Wunsch erschaffen",
    "Lebendige Gemaelde an allen Waenden",
    "Kinder erfinden die Zukunft",
    "Freundliche Roboter an jedem Arbeitsplatz",
    "Grenzenlose Kreativitaet fuer alle",
    "Fliegende Buecherregale mit Geschichten",
    "Vogelgezwitscher als Hintergrundmusik",
    "Regen aus Blumenblueten im Fruehling",
    "Selbstkochende Kochtoepfe",
    "Schmetterlinge als fliegende Briefe",
    "Inseln aus Marshmallows im Ozean",
    "Lachende Sonne am Morgen",
    "Automatische Komplimente in der Luft",
    "Musikinstrumente spielen sich selbst im Park",
    "Virtuelle Realitaet, die Traeume erschafft",
    "Katzen als fliegende Begleiter",
    "Friedliche Roboterrevolution weltweit",
    "Zukunft mit freiem Zugang zu allem",
    "Schwebende Kaffeetassen",
    "Bananen schenken Glueck",
    "Tanzende Einhoerner",
    "Glitzernde Regenbogenstrahlen",
    "Schokolade als Medizin",
    "Sprechen mit Pflanzen",
    "Kissen sprechen Geschichten",
    "Freude in Regentropfen",
    "Fliegende Donuts",
    "Laecheln als Sportart",
    "Wolkensurfen am Abend",
    "Automatische Umarmungen",
    "Schwimmende Buecher",
    "Lachen heilt Zeitreisen",
    "Singen macht unsichtbar",
    "Kuschelnde Roboterarmee",
    "Himmel aus Marshmallows",
    "Eiscreme fuer alle",
    "Magische Sonnenuntergaenge",
    "Sonnenschein im Regen",
    "Pizza teleportiert sich",
    "Regenbogenfarbene Katzen",
    "Fliegende Gummibaerchen",
    "Unendliche Achterbahnen",
    "Singende Kuehlschraenke",
    "Wolken als Huepfkissen",
    "Hochzeiten mit Konfetti",
    "Automatische Gluecksmomente",
    "Tanzen in Zeitlupe",
    "Kaffeeklatsch mit Aliens",
    "Luftballons statt Autos",
    "Liebe in jeder Bluete",
    "Spruehregen aus Parfuem",
    "Sonnige Schneeflocken",
    "Bienen als Postboten",
    "Lachende Blumenbeete",
    "Zauberhafte Wasserrutschen",
    "Schokoladenbrunnen im Park",
    "Sofas, die Geschichten erzaehlen",
    "Friedliche Roboter-Ozeane",
    "Selbstkochende Gourmetkueche",
    "Kaffeebaeume am Strassenrand",
    "Regen aus Gluecksmomenten",
    "Ewige Karnevalsstimmung",
    "Freude in jeder Wolke",
    "Geschichten in Sandduenen",
    "Hologramm-Sonnenschirme",
    "Laechelnde Mondlandschaft",
    "Kakao fliesst in Baechen",
    "Singende Berggipfel",
    "Zeitlupe fuer den Alltag",
    "Hologramm-Baeume im Wohnzimmer",
    "Lachen als Universitaetsabschluss",
    "Freundliche Roboter als Babysitter",
    "Mondschokolade aus dem Supermarkt",
    "Teleportation fuer den taeglichen Pendelverkehr",
    "Autos, die miteinander tanzen",
    "Wassergaerten in jedem Stadtpark",
    "Sonnenstrahlen als Heilmittel",
    "Unsichtbare Huepfburgen im Buero",
    "Schwebende Bibliotheken im Himmel",
    "Lichtspiele statt Strassenlaternen",
    "Wolken als Rutschen im Sommer",
    "Baeume als Klangquellen",
    "Eiscreme fuer alle Altersgruppen",
    "Buecher, die bei Bedarf erscheinen",
    "Sterne als Haengematten im Himmel",
    "Fliegende Lesezeichen",
    "Lachen als offizielle Waehrung",
    "Worte, die in der Luft tanzen",
    "Gruener Regen, der die Erde heilt",
    "Auto-pilotierte Waeschestaender",
    "Regen aus Pusteblumen",
    "Ewige junge Pflanzen in jeder Ecke",
    "Sonnenbrillen fuer Gedanken",
    "Blumen, die Musik machen",
    "Kuschelnde Baeume im Winter",
    "Freundliche Roboter in jeder Strassenbahn",
    "Fruehstueck per Teleportation",
    "Lachende Kaktusse als Haustiere",
    "Papierschmetterlinge als Flugzeuge",
    "Sich selbst verdauende Mahlzeiten",
    "Gespraechspartner in den Sternen",
    "Ewige Sommernaechte bei Vollmond",
    "Virtuelle Wanderungen durch Buecher",
    "Baeume, die in verschiedenen Toenen singen",
    "Eiscreme, die nie schmilzt",
    "Mondlichter im Taschenformat",
    "Magische Taschen, die alles speichern",
    "Kunstwerke aus Regenbogenfarben",
    "Unendliche Puzzles fuer alle",
    "Schwebende Regenschirme im Wind",
    "Sonnenbrillen, die das Wetter aendern",
    "Bienen als Postboten",
    "Schwebende Cafés in den Wolken",
    "Musik, die durch die Luft fliesst",
    "Fliegende Pflanzen in jeder Stadt",
    "Autos, die sich von alleine parken",
    "Regen aus Glitzerstaub",
    "Baeume, die in der Nacht leuchten",
    "Tiere, die durch Gedanken gesteuert werden",
    "Sonne, die immer die perfekte Temperatur hat",
    "Sich selbst fuellende Wasserflaschen",
    "Buecher, die sich selbst lesen",
    "Unendliche Spielplaetze auf der ganzen Welt",
    "Blumen, die den Weg weisen",
    "Kaffee, der den Tag verlaengert",
    "Unendliche Baeder in Regenbogenfarben",
    "Sich selbst reparierende Strassen",
    "Musik, die den Regen vertreibt",
    "Freundliche Roboter als Nachbarn",
    "Kuschelnde Wolken zum Schlafen",
    "Fliegende Schmetterlinge als Brieftraeger",
    "Sich selbst sauberhaltende Straende",
    "Wasserfaelle aus Schokoladensirup",
    "Tanzen, um die Zeit anzuhalten",
    "Kaffee, der deine Laune hebt",
    "Lachende Voegel, die den Tag begruessen",
    "Tanzen, um die Gedanken zu ordnen",
    "Ewige Fruehlingswinde",
    "Fliegende Inseln fuer jedes Abenteuer",
    "Virtuelle Gaerten zum Entspannen",
    "Baeume, die Musikstuecke komponieren",
    "Licht, das in allen Farben des Regenbogens leuchtet",
    "Regen, der aus bunter Pappe besteht",
    "Freundliche Baeren als Taxis",
    "Automatische Kuschelroboter",
    "Fliegende Schokoladenkekse",
    "Regenbogen-Strassen, die den Weg weisen",
    "Mondlichter, die den Weg zum Traeumen ebnen",
    "Schwimmende Maerkte in der Luft",
    "Ewige Sonne fuer alle, die es wollen",
    "Voegel, die Wuensche erfuellen",
    "Sich selbst kochende Mahlzeiten in Minuten",
    "Fliegende Heissluftballons in allen Formen",
    "Kreativitaet als universelles Recht",
    "Tanzende aeste im Wind",
    "Sich selbst reparierende Haeuser",
    "Pflanzen, die mit dir sprechen",
    "Sonnenstrahlen, die den Winter vertreiben",
    "Farbige Fluesse, die in den Himmel muenden",
    "Freundliche Roboter als Reisebegleiter",
    "Schmetterlinge, die den Fruehling ankuendigen",
    "Lachen als Heilmittel fuer alles",
    "Katzen, die Geheimnisse der Welt kennen"
};

// Configuration constants
constexpr uint8_t DISPLAY_WIDTH = 64;
constexpr uint8_t DISPLAY_HEIGHT = 64;
constexpr uint8_t BRIGHTNESS = 80;  // 0-255
constexpr uint8_t SLEEP_BUTTON = 0;  // GPIO0 - BOOT button

// Time configuration (in microseconds)
const uint64_t AWAKE_TIME_US = 15ULL * 3600ULL * 1000000ULL;  // 15 hours
const uint64_t SLEEP_TIME_US = 9ULL * 3600ULL * 1000000ULL;   // 9 hours

// RTC variable that persists during deep sleep
RTC_DATA_ATTR uint16_t elapsed_minutes = 0;  // Minutes since last wake

// Forward declarations of classes
class DisplayManager;
class ContentManager;

// Global variables
DisplayManager* display;
ContentManager* content;

// Classes definitions
class ContentManager {
private:
    static const size_t ARRAY_SIZE = sizeof(utopias) / sizeof(utopias[0]);

public:
    String getRandomMessage() {
        size_t index = random(ARRAY_SIZE);
        Serial.printf("Selected message %d of %d: %s\n", index, ARRAY_SIZE, utopias[index]);
        return String(utopias[index]);
    }
};

class DisplayManager {
private:
    MatrixPanel_I2S_DMA* display;

public:
    DisplayManager() {
        HUB75_I2S_CFG config(DISPLAY_WIDTH, DISPLAY_HEIGHT, 1);
        config.gpio.e = 32;
        config.clkphase = false;
        config.driver = HUB75_I2S_CFG::FM6124;

        display = new MatrixPanel_I2S_DMA(config);
        display->begin();
        display->setBrightness8(BRIGHTNESS);
        display->clearScreen();
    }

    void clearScreen() { display->clearScreen(); }
    void setBrightness8(uint8_t b) { display->setBrightness8(b); }
    void setCursor(int16_t x, int16_t y) { display->setCursor(x, y); }
    void print(const char* text) { display->print(text); }
    void printf(const char* format, ...) {
        char buf[32];  // Fixed size, sufficient for our needs
        va_list args;
        va_start(args, format);
        vsnprintf(buf, sizeof(buf), format, args);
        va_end(args);
        display->print(buf);
    }

    void setTextColor(uint8_t r, uint8_t g, uint8_t b) {
        display->setTextColor(display->color444(r, g, b));
    }


    void updateDisplay(const String& message) {
        clearScreen();
        
        // Generate random colors (values between 1-7 for good visibility)
        uint8_t r = random(1, 8);
        uint8_t g = random(1, 8);
        uint8_t b = random(1, 8);
        setTextColor(r, g, b);
        
        const int16_t lineHeight = 9;  // Height of each text line
        const int16_t maxCharsPerLine = 10;  // Force 10 characters per line
        
        // First pass: count lines to calculate vertical centering
        String words[10];  // Array to store words
        int wordCount = 0;
        
        // Split message into words
        String currentWord = "";
        for (size_t i = 0; i <= message.length(); i++) {
            char c = (i < message.length()) ? message[i] : ' ';
            if (c == ' ' || i == message.length()) {
                if (currentWord.length() > 0) {
                    words[wordCount++] = currentWord;
                    currentWord = "";
                }
            } else {
                currentWord += c;
            }
        }
        
        // Count total lines needed
        int totalLines = 0;
        String lines[8];  // Store final lines for second pass
        String currentLine = "";
        
        for (int i = 0; i < wordCount; i++) {
            String word = words[i];
            
            if ((currentLine.length() + (currentLine.length() > 0 ? 1 : 0) + word.length()) <= maxCharsPerLine) {
                if (currentLine.length() > 0) {
                    currentLine += " ";
                }
                currentLine += word;
            } else {
                if (currentLine.length() > 0) {
                    lines[totalLines++] = currentLine;
                    currentLine = "";
                }
                
                while (word.length() > maxCharsPerLine) {
                    lines[totalLines++] = word.substring(0, maxCharsPerLine);
                    word = word.substring(maxCharsPerLine);
                }
                currentLine = word;
            }
        }
        if (currentLine.length() > 0) {
            lines[totalLines++] = currentLine;
        }
        
        // Calculate starting Y position for vertical centering
        int16_t startY = (DISPLAY_HEIGHT - (totalLines * lineHeight)) / 2;
        if (startY < 0) startY = 0;
        
        // Second pass: actually draw the centered text
        for (int i = 0; i < totalLines; i++) {
            String line = lines[i];
            // Calculate X position for horizontal centering of this line
            int16_t startX = (DISPLAY_WIDTH - (line.length() * 6)) / 2;  // 6 pixels per character
            if (startX < 0) startX = 0;
            
            setCursor(startX, startY + (i * lineHeight));
            print(line.c_str());
        }
    }
};

// Function implementations
void goToSleep() {
    Serial.println("Going to sleep now");
    display->clearScreen();
    display->setBrightness8(0);
    
    esp_sleep_enable_timer_wakeup(SLEEP_TIME_US);
    Serial.printf("Sleep time set to %llu seconds\n", SLEEP_TIME_US / 1000000ULL);
    
    Serial.flush();
    delay(100);
    esp_deep_sleep_start();
}

void setup() {
    Serial.begin(115200);
    Serial.println("\nFramed Utopia Starting Up");
    Serial.printf("Will stay awake for %llu hours\n", AWAKE_TIME_US / 3600000000ULL);
    
    // Setup sleep button as input with internal pull-up
    pinMode(SLEEP_BUTTON, INPUT_PULLUP);
    
    display = new DisplayManager();
    content = new ContentManager();
    
    // Display new message on wake
    display->updateDisplay(content->getRandomMessage());
}

void loop() {
    static unsigned long start_time = millis();
    static unsigned long lastButtonCheck = 0;
    unsigned long now = millis();
    
    // Check button state with debounce
    if ((now - lastButtonCheck) >= 50) {
        lastButtonCheck = now;
        if (digitalRead(SLEEP_BUTTON) == LOW) {  // Button is pressed (active low)
            Serial.println("Sleep button pressed, going to sleep");
            goToSleep();
        }
    }
    
    // Check if awake time has elapsed
    if ((now - start_time) >= (AWAKE_TIME_US / 1000ULL)) {  // Convert microseconds to milliseconds
        Serial.println("Awake time reached, going to sleep");
        goToSleep();
    }
}
