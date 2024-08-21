import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class Sequencial {

    public static String lerArquivo(String caminho) throws IOException {
        return new String(Files.readAllBytes(Paths.get(caminho)));
    }

    public static void salvarArquivo(String caminho, String conteudo) throws IOException {
        Files.write(Paths.get(caminho), conteudo.getBytes(), StandardOpenOption.CREATE);
    }

    public static void main(String[] args) {
        String nomeDoArquivo = "arquivos/DNA.txt";
        String nomeDoArquivoSaida = "arquivos/DNA_transcrito.txt";

        String conteudo;
        try {
            conteudo = lerArquivo(nomeDoArquivo);
        } catch (IOException e) {
            System.out.println("Erro ao abrir o arquivo!");
            return;
        }

        char[] fita = conteudo.toCharArray();

        long tempoInicial = System.currentTimeMillis();

        for (int i = 0; i < fita.length; i++) {
            switch (Character.toUpperCase(fita[i])) {
                case 'A':
                    fita[i] = 'T';
                    break;
                case 'C':
                    fita[i] = 'G';
                    break;
                case 'T':
                    fita[i] = 'A';
                    break;
                case 'G':
                    fita[i] = 'C';
                    break;
            }
        }

        long tempoFinal = System.currentTimeMillis();
        long tempoDecorrido = tempoFinal - tempoInicial;

        System.out.printf("Tempo decorrido: %d ms%n", tempoDecorrido);

        try {
            salvarArquivo(nomeDoArquivoSaida, new String(fita));
            System.out.println("Arquivo transcrito salvo em: " + nomeDoArquivoSaida);
        } catch (IOException e) {
            System.out.println("Erro ao salvar o arquivo transcrito!");
        }
    }
}
