# LogNet - A Fast and Flexible Logging System

![Cool image of LogNet](docs/images/img.png "Cool image of LogNet")

LogNet is an open-source logging system designed for services that require efficient and flexible logging capabilities. It provides a high-performance solution for receiving and managing logs using the UDP protocol. LogNet allows users to send logs as "Atoms," which are structured log entries that contain various metadata and can be linked together to track the flow within a system.

## Features

- **Atom-based Logging**: LogNet organizes logs as Atoms, which are structured log entries containing information such as type, level, timestamp, namespace, section, key, value, and IDs. Atoms can be linked together to create a flow of logs, enabling easy tracking and analysis.

- **Flexible Log Levels**: LogNet supports multiple log levels, including INFO, ERROR, DEBUG, and TEST, allowing you to categorize logs based on their importance or severity.

- **Efficient Data Storage**: The linked list data structure used by LogNet ensures efficient storage and retrieval of logs. Logs can be easily added or removed, making it convenient to manage log entries in real-time.

- **UDP Protocol**: LogNet utilizes the UDP protocol, which offers a connectionless and faster alternative to TCP for log transmission. This makes LogNet ideal for high-performance logging scenarios where speed is crucial.

- **Plugin System**: LogNet provides a plugin system that allows for extending the functionality of the logging system. Plugins can receive the log stream via a ZMQ channel and perform various tasks such as storing logs in databases, writing to files, or implementing alerting systems.

- **Hot Plug and Play**: The LogNet plugin system supports hot plug and play, meaning that plugins can be dynamically added or removed without disrupting the logging process. The system's heartbeat feature detects active plugins listening to the atom stream channel on ZMQ.

- **Multi-language SDKs**: LogNet aims to provide SDKs for multiple programming languages, including Python, Go, C++, JavaScript, and more. These SDKs enable developers to seamlessly integrate their applications with LogNet and send logs efficiently.

## Dependencies
* **[mongoose](https://github.com/cesanta/mongoose)**: Mongoose is a powerful and easy to use HTTP server library for C

## Getting Started

To get started with LogNet, follow these steps:

1. **Installation**: Clone the LogNet repository from GitHub and compile the C language source code. Make sure you have the necessary dependencies installed.

2. **Integration**: Use the provided SDKs to integrate LogNet into your application. Choose the SDK that matches your programming language and follow the instructions in the respective documentation.

3. **Configure Logging**: Set up the log levels, namespaces, and other configurations according to your requirements. Refer to the LogNet documentation for detailed instructions on configuration options.

4. **Start Logging**: Begin logging by creating Atoms and sending them to the LogNet system using the SDK. You can link multiple Atoms to track the flow of your system's components.

5. **Extend Functionality with Plugins**: Take advantage of LogNet's plugin system to enhance the capabilities of your logging system. Develop plugins to process logs, store them in databases, generate alerts, or perform any custom actions.

## Contributing

LogNet welcomes contributions from the open-source community. If you'd like to contribute to the project, please follow the guidelines outlined in the CONTRIBUTING.md file in the repository. Contributions can range from bug fixes and feature implementations to documentation improvements and code optimizations.

## License

LogNet is licensed under the [MIT License](https://opensource.org/licenses/MIT), which allows for both personal and commercial use of the software.

## Support

For support or any questions related to LogNet, please refer to the project's GitHub repository. Open an issue on the repository page, and the maintainers and community members will assist you.

## Acknowledgments

LogNet is developed and maintained by a dedicated team of contributors who have generously devoted their time

and expertise to create a robust and efficient logging system. The project relies on various open-source libraries and tools, and we extend our gratitude to their respective developers and maintainers.

We would also like to thank the open-source community for their valuable feedback, bug reports, and feature suggestions, which have helped shape LogNet into what it is today. Your support and involvement are greatly appreciated.

