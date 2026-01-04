# MapGenerator

O **MapGenerator** é uma ferramenta auxiliar para o projeto Gods-Defense, destinada à geração e manipulação de mapas utilizados no jogo. Este utilitário facilita a criação, edição e exportação de mapas em formatos compatíveis com o motor do jogo.

## Funcionalidades

- Interface gráfica para criação e edição de mapas
- Adição e remoção de ondas de inimigos (waves), com suporte a chefes (boss)
- Adição de checkpoints (pontos de passagem) no mapa
- Carregamento de imagens de mapa em formato PNG
- Salvamento do mapa editado em formato PNG
- Geração de arquivo XML do mapa, incluindo:
	- Nome, descrição, ouro inicial, vidas
	- Informações de colisão do mapa
	- Caminhos e checkpoints
	- Ondas de inimigos, com atributos como intervalo de spawn, descrição, quantidade, pasta do inimigo e se é boss
- Validação dos campos obrigatórios antes de gerar o mapa

## Estrutura
O diretório `MapGenerator/` contém:
- `src/` — Código-fonte principal do MapGenerator
- `lib/` — Bibliotecas auxiliares utilizadas pelo MapGenerator

## Como compilar e rodar

No terminal, dentro do diretório `tools/MapGenerator/`, execute:

```sh
javac -cp lib/dom4j-1.6.1.jar $(find src -name "*.java")
java -cp src:lib/dom4j-1.6.1.jar AnyKey.Main
```

Esses comandos irão compilar todos os arquivos Java e iniciar a interface gráfica do MapGenerator.

## Dependências
- Certifique-se de possuir as dependências necessárias instaladas (verifique possíveis arquivos README ou documentação adicional em `src/` ou `lib/`).

## Contribuição
Contribuições são bem-vindas! Sinta-se à vontade para abrir issues ou pull requests com melhorias, correções ou novas funcionalidades.

## Licença
Consulte o arquivo LICENSE na raiz do repositório para informações sobre licenciamento.
