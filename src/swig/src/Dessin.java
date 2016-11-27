import processing.core.PVector;
import java.util.List;
import java.util.ArrayList;

public class Dessin {
    public static String VERSION="0.0.4";

    public static void main(String[] argv) {
        // Ceci est un test.
        for(PVector p : etoile(0, 0, 100, 16)) {
            System.out.printf("(%.2f; %.2f)\n", p.x, p.y);
        }
    }

    public static List<PVector> etoile(float cx, float cy, float r) {
        // Une puissance de deux c'est bien.
        return etoile(cy, cy, r, 256);
    }

    public static List<PVector> etoile(float cx, float cy, float r, float steps) {
        List<PVector> points = new ArrayList<PVector>();
        float[] x = new float[]{0};
        float[] y = new float[]{0};
        for(float i=0; i <= 1; i += 1/steps) {
            if (shared._etoile(x, y, cx, cy, r, i)) {
                points.add(new PVector(x[0], y[0]));
            } else {
                System.err.printf("Appel à etoile(%f, %f, %f, %d) a échoué.", cx, cy, r, i);
                return points;
            }
        }
        return points;
    }
}
