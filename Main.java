//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    public static void main(String[] args) {
        //Creamos los objetos hilo y les asignamos un nombre
        Hilo hilo1 = new Hilo("Hilo1");
        Hilo hilo2 = new Hilo("Hilo2");
        //Inicializamos ambos hilos
        hilo1.start();
        hilo2.start();
    }
}
