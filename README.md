# DeferredBT

## Overview

**DeferredBT** is an action behavior tree (BT) node that executes a provided behavior tree based on either the path to an XML file or its raw content, along with a list of plugins to load. 

To use this node, simply include it in your BT as you would any other custom action BT node.

## Input Ports

The **DeferredBT** node has four input ports to specify the BT to defer. Depending on your needs, only a few of these ports will be used:

```cpp
static BT::PortsList providedPorts()
{
  return BT::PortsList(
    {
      BT::InputPort<std::string>("bt_pkg"), // package where the XML is located
      BT::InputPort<std::string>("rel_path"), // relative path to the XML
      BT::InputPort<std::string>("xml"), // XML corresponding to the BT to be executed
      BT::InputPort<std::vector<std::string>>("plugins"), // plugins to load
    });
}
```

## Usage

### Specifying a path to an XML File

If you want to specify a path to an XML file:

* Use the **bt_pkg** port to specify the package where the file is located.
* Set the **rel_path** to the relative path to the XML file within this package.

### Providing raw content of the BT

If you want to provide the raw content of the BT to be run:

* Use the **xml** port to supply the behavior to this BT action node.

### Specifying plugins

In both cases (path or content), the **plugins** input port needs to be used to inform the **DeferredBT** node of the necessary plugins it needs to load to run the BT.
