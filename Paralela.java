import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.util.concurrent.Executors;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.TimeUnit;

public class Paralela {

    public static void main(String[] args) {
        String nomeDoArquivo = "arquivos/DNA.txt";
        String conteudo;
        
        try {
            conteudo = new String(Files.readAllBytes(Paths.get(nomeDoArquivo)));
        } catch (IOException e) {
            System.out.println("Erro ao abrir o arquivo!");
            return;
        }
        
        char[] fita = conteudo.toCharArray();
        long tempoInicial = System.currentTimeMillis();

        int numThreads = 4;
        ExecutorService executor = Executors.newFixedThreadPool(numThreads);
        int tamanhoDoBloco = (int) Math.ceil((double) fita.length / numThreads);

        for (int i = 0; i < numThreads; i++) {
            final int inicio = i * tamanhoDoBloco;
            final int fim = Math.min(inicio + tamanhoDoBloco, fita.length);
            executor.submit(() -> {
                for (int j = inicio; j < fim; j++) {
                    switch (Character.toUpperCase(fita[j])) {
                        case 'A':
                            fita[j] = 'T';
                            break;
                        case 'C':
                            fita[j] = 'G';
                            break;
                        case 'T':
                            fita[j] = 'A';
                            break;
                        case 'G':
                            fita[j] = 'C';
                            break;
                    }
                }
            });
        }

        executor.shutdown();
        try {
            if (!executor.awaitTermination(1, TimeUnit.MINUTES)) {
                executor.shutdownNow();
            }
        } catch (InterruptedException e) {
            executor.shutdownNow();
        }

        long tempoFinal = System.currentTimeMillis();
        long tempoDecorrido = tempoFinal - tempoInicial;

        System.out.printf("Tempo decorrido: %d ms%n", tempoDecorrido);

        String nomeDoArquivoSaida = "arquivos/DNA_transcrito.txt";
        try {
            Files.write(Paths.get(nomeDoArquivoSaida), new String(fita).getBytes(), StandardOpenOption.CREATE);
            System.out.println("Arquivo transcrito salvo em: " + nomeDoArquivoSaida);
        } catch (IOException e) {
            System.out.println("Erro ao salvar o arquivo transcrito!");
        }
    }
}
