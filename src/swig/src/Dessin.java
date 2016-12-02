import processing.core.PApplet;
import processing.core.PVector;
import java.util.List;
import java.util.ArrayList;


public class Dessin {
    public static String VERSION="0.0.4";

    public static void main(String[] argv) {
        System.out.println("Ceci est un test");
        shared.getCaller().setCallback(new Callback(){
            @Override
            public void moveServos() {
                System.out.printf("moveServos\n");
            }

            @Override
            public void toAngle(float x, float y) {
                System.out.printf("toAngle %f, %f\n", x, y);
            }
        });

        shared.etoile(0, 0, 100);
    }

    public static void setPApplet(final PApplet pApplet, final float zoom) {
        shared.getCaller().setCallback(new Callback(){
            private PVector old;
            private PVector current = new PVector(0, 0);

            @Override
            public void moveServos() {
                pApplet.line(old.x, old.y, current.x, current.y);
                //pApplet.delay(100);
            }

            @Override
            public void toAngle(float x, float y) {
                //pApplet.println("to ", x, y);
                old = current;
                current = new PVector(x * zoom, y * zoom);
            }
        });
    }
}
