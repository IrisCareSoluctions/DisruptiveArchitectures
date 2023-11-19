# DISRUPTIVE ARCHITECTURES: IOT, IOB & IA

## IrisCareSoluctions :eyes:

Prevenção do Retinoblastoma por meio da análise de imagem.


# Integrantes
- RM93915 Jaelson dos Santos
- RM94311	Marcos Henrique Bilobram dos Santos
- RM96320	Nathália de Queiroz Maia
- RM94972	Rafaela Gomes da Silva
- RM93613	Vinicius de Oliveira


# <span style="color: #63C71F;">Protótipo</span>
Sensor Ultrassom HC-SR04 e Buzzer

Sensor ultrassom simplificado HC-SR04 no Arduino. Ativa o Buzzer toda vez que sensor captar objeto a certa distância.

![IrisCareSoluctions](https://github.com/IrisCareSoluctions/DisruptiveArchitectures/assets/99452621/51ec9e50-22b7-43c6-9217-dd477968ae64)

# IrisCare Solutions - Monitor de Sensor Ultrassônico

Este é um projeto que utiliza a biblioteca PyQt5 em conjunto com pyqtgraph para criar uma interface gráfica que monitora e exibe dados em tempo real de um sensor ultrassônico.

![image](https://github.com/IrisCareSoluctions/DisruptiveArchitectures/assets/99452621/cae6371e-ffa4-4295-a806-ab70ce17ef8c)


## Pré-requisitos

- Python 3.x
- PyQt5
- pyqtgraph
- pandas
- numpy

Você pode instalar as dependências utilizando o seguinte comando:

```bash
pip install PyQt5 pyqtgraph pandas numpy
```

# Funcionalidades
Monitoramento em Tempo Real: A interface exibe um gráfico em tempo real com dados do sensor ultrassônico.

Informações dos Integrantes: Você pode acessar informações sobre os integrantes do projeto clicando no botão correspondente na interface.

# Estrutura do Código

- main.py: O script principal que inicia a aplicação.
- sensor_interface.py: Contém a definição da classe Tela_Sensor, responsável pela interface do monitor de sensor.
- integrantes_interface.py: Contém a definição da classe Tela_Integrantes, responsável pela interface de informações sobre os integrantes.
- dados.py: Contém a função data(df) que gera dados simulados para o sensor ultrassônico.
./Arquivos/Imagens: Contém imagens utilizadas na interface.
