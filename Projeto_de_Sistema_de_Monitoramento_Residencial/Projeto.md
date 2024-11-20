# Projeto de Sistema de Monitoramento Residencial (UFSC)

Este repositório contém o código-fonte do projeto de **Sistema de Monitoramento Residencial**, desenvolvido no âmbito da disciplina de **Microprocessadores e Microcontroladores** da **Universidade Federal de Santa Catarina (UFSC)**.

## Descrição do Projeto

O **Sistema de Monitoramento Residencial** é um sistema de automação destinado a aumentar a segurança e o conforto dentro de um ambiente residencial. O projeto monitora a **temperatura** e detecta a **presença de gás** no ambiente, tomando ações corretivas automaticamente. Desenvolvido em linguagem C, o sistema é implementado em um microcontrolador **PIC16F877A**.

## Funcionalidades Principais

1. **Controle de Temperatura**  
   O sistema monitora a temperatura ambiente em tempo real e ajusta automaticamente os dispositivos de aquecimento ou resfriamento, garantindo que a temperatura se mantenha dentro de um intervalo confortável e seguro.

2. **Detecção de Gás**  
   Utilizando um sensor de gás, o sistema detecta vazamentos ou a presença de gás no ambiente e aciona alertas visuais através de um **display LCD** e um **LED de aviso**, garantindo uma resposta imediata a qualquer situação de risco.

3. **Interface de Usuário**  
   O sistema apresenta informações sobre a **temperatura ambiente** e o **estado da detecção de gás** no **LCD**, facilitando a interação e monitoramento do usuário.

4. **Segurança**  
   Medidas de segurança são implementadas para controlar e limitar o funcionamento de dispositivos, como aquecedores e ventiladores, em situações críticas, além de garantir a integridade do sistema no caso de vazamentos de gás.

## Autores

- **Alisson Pereira Ferreira** (Matrícula: 22250769, E-mail: alissonpef@gmail.com)  
- **Dennis Paul Paz Lopez** (Matrícula: 22250970, E-mail: dppazlopez@gmail.com)

## Contato

Para dúvidas ou informações adicionais, entre em contato com os autores do projeto.

## Configuração do Projeto

### Hardware
- **Microcontrolador:** PIC16F877A
- **Componentes adicionais:**  
  - Display LCD
  - Sensor de temperatura
  - Sensor de gás
  - Lâmpada
  - Ventilador
  - LED

### Software
- **Ambiente de Desenvolvimento:** MikroC
- **Bibliotecas:** Sensor de Gás

## Instruções de Uso

### 1. Configuração do Hardware
- Conecte os **sensores de temperatura** e **gás**, o **LCD**, e os dispositivos de controle (como **lâmpada** e **ventilador**) ao microcontrolador conforme a pinagem definida no código-fonte.

### 2. Configuração do Software
- Abra o projeto no **Proteus** (ou outra ferramenta de simulação de sua preferência).
- Carregue o código compilado no microcontrolador utilizando o **MikroC** ou IDE de sua escolha.

### 3. Execução
- Após alimentar o sistema, observe as leituras da **temperatura** no LCD.
- O sistema ajustará automaticamente a temperatura com base nas leituras do sensor e acionará o alerta de gás, se detectado, utilizando os **alertas visuais** no LCD e no **LED**.

## Lógica do Código

O código fonte está estruturado para realizar as seguintes operações:

- **Controle de Temperatura:** A leitura do sensor de temperatura determina quando os dispositivos de controle (aquecedor ou ventilador) devem ser ativados ou desativados.
- **Detecção de Gás:** O sensor de gás verifica continuamente o ambiente para a presença de gás. Se detectado, o sistema gera um alerta visual para notificar o usuário.
- **Interface Visual:** O **LCD** exibe a **temperatura atual** e a **situação do sensor de gás**, enquanto o **LED** fornece um aviso visual de alerta.

## Universidade Federal de Santa Catarina

- **Curso:** Engenharia de Computação  
- **Disciplina:** Microprocessadores e Microcontroladores  
- **Professor:** Rodrigo Vinícius Mendonça Pereira

Este projeto visa proporcionar uma introdução prática ao uso de microcontroladores em sistemas de automação residencial, integrando sensores e dispositivos de controle de forma eficaz e segura.
