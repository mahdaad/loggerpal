# Loggerpal - A Fast and Flexible Logging System

![Cool image of Loggerpal](docs/images/img.png "Cool image of Loggerpal")

Loggerpal is an open-source logging system designed for services that require efficient and flexible logging capabilities. It provides a high-performance solution for receiving and managing logs using the UDP protocol. Loggerpal allows users to send logs as "Atoms," which are structured log entries that contain various metadata and can be linked together to track the flow within a system.

## Features

- **Atom-based Logging**: Loggerpal organizes logs as Atoms, which are structured log entries containing information such as type, level, timestamp, namespace, section, key, value, and IDs. Atoms can be linked together to create a flow of logs, enabling easy tracking and analysis.

- **Flexible Log Levels**: Loggerpal supports multiple log levels, including INFO, ERROR, DEBUG, and TEST, allowing you to categorize logs based on their importance or severity.

- **Efficient Data Storage**: The linked list data structure used by Loggerpal ensures efficient storage and retrieval of logs. Logs can be easily added or removed, making it convenient to manage log entries in real-time.

- **UDP Protocol**: Loggerpal utilizes the UDP protocol, which offers a connectionless and faster alternative to TCP for log transmission. This makes Loggerpal ideal for high-performance logging scenarios where speed is crucial.

- **Plugin System**: Loggerpal provides a plugin system that allows for extending the functionality of the logging system. Plugins can receive the log stream via a ZMQ channel and perform various tasks such as storing logs in databases, writing to files, or implementing alerting systems.

- **Hot Plug and Play**: The Loggerpal plugin system supports hot plug and play, meaning that plugins can be dynamically added or removed without disrupting the logging process. The system's heartbeat feature detects active plugins listening to the atom stream channel on ZMQ.

- **Multi-language SDKs**: Loggerpal aims to provide SDKs for multiple programming languages, including Python, Go, C++, JavaScript, and more. These SDKs enable developers to seamlessly integrate their applications with Loggerpal and send logs efficiently.

## Dependencies
* **[mongoose](https://github.com/cesanta/mongoose)**: Mongoose is a powerful and easy to use HTTP server library for C

## Getting Started

To get started with Loggerpal, follow these steps:

1. **Installation**: Clone the Loggerpal repository from GitHub and compile the C language source code. Make sure you have the necessary dependencies installed.

2. **Integration**: Use the provided SDKs to integrate Loggerpal into your application. Choose the SDK that matches your programming language and follow the instructions in the respective documentation.

3. **Configure Logging**: Set up the log levels, namespaces, and other configurations according to your requirements. Refer to the Loggerpal documentation for detailed instructions on configuration options.

4. **Start Logging**: Begin logging by creating Atoms and sending them to the Loggerpal system using the SDK. You can link multiple Atoms to track the flow of your system's components.

5. **Extend Functionality with Plugins**: Take advantage of Loggerpal's plugin system to enhance the capabilities of your logging system. Develop plugins to process logs, store them in databases, generate alerts, or perform any custom actions.

## Contributing

Loggerpal welcomes contributions from the open-source community. If you'd like to contribute to the project, please follow the guidelines outlined in the CONTRIBUTING.md file in the repository. Contributions can range from bug fixes and feature implementations to documentation improvements and code optimizations.

## License

Loggerpal is licensed under the [MIT License](https://opensource.org/licenses/MIT), which allows for both personal and commercial use of the software.

## Support

For support or any questions related to Loggerpal, please refer to the project's GitHub repository. Open an issue on the repository page, and the maintainers and community members will assist you.

## Acknowledgments

Loggerpal is developed and maintained by a dedicated team of contributors who have generously devoted their time

and expertise to create a robust and efficient logging system. The project relies on various open-source libraries and tools, and we extend our gratitude to their respective developers and maintainers.

We would also like to thank the open-source community for their valuable feedback, bug reports, and feature suggestions, which have helped shape Loggerpal into what it is today. Your support and involvement are greatly appreciated.

