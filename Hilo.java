public class Hilo extends Thread {
    private String NombreHilo = "";
    //Se define en el constructor el nombre del hilo
    public Hilo(String HiloGeneral) {
        setNombreHilo(HiloGeneral);
    }
    //Se definen los métodos para obtener o establecer el recurso nombreHilo
    public void setNombreHilo(String nombreHilo) {
        this.NombreHilo = nombreHilo;
    }
    public String getNombreHilo() {
        return NombreHilo;
    }
    public long  obtenerFecha() throws InterruptedException {
        int segundos=0;
        int minutos = 0;
        long tiempoInicial = 0;
        long tiempoFinal = 0;
        long tiempoTranscurrido=0;
        int segundosTranscurridos=0;
        int minutosTranscurridos=0;
        String fecha;

        //se establecen los contadores para los milisegundos iniciales y finales
        tiempoInicial = System.currentTimeMillis();

        for(int i = 0; i<10000; i++){
        sleep(1);
        }

        tiempoFinal = System.currentTimeMillis();

        //Se calcula el tiempo transcurrido como una diferencia entre el tiempo inicial
        //y el tiempo final
        tiempoTranscurrido = tiempoFinal - tiempoInicial;
        segundosTranscurridos = (int) (tiempoTranscurrido / 1000);
        minutosTranscurridos = segundosTranscurridos / 60;
        //Se imprime a pantalla el tiempo transcurrido en segundos y minutos
        System.out.println("Tiempo transcurrido en segundos: " + segundosTranscurridos);
        System.out.println("Tiempo transcurrido en minutos: " + minutosTranscurridos);
        //se retorna el tiempo final
        return tiempoFinal;
    }

    //Se sobrecarga el método run
@Override
public void run() {
    //Se muestra a pantalla el nombre del Hilo
    System.out.println("Este es el hilo:" + getNombreHilo());
    try {
        System.out.println("El tiempo de ejecucion es:"+obtenerFecha());
    } catch (InterruptedException e) {
        throw new RuntimeException(e);
    }
}

}
