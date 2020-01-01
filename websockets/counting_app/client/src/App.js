import React from 'react';

class SimpleContent extends React.Component {

  constructor(props) {
    super(props)
    this.state = {
      header: props.header,
      value: props.value
    }
  }

  setValue = (value) => {
    this.setState({ value: value });
  }

  render() {
    return (
      <div>
        <span>{this.state.header}{this.state.value}</span>
      </div>
    );
  }

}

class App extends React.Component {

  constructor(props) {
    super(props);
    this.state = {
      websocket: null,
      receivedCounterValue: 0,
      numberOfConnectedUsers: 0
    };
    this.counterValueRef = React.createRef();
    this.numberOfConnectedUsersRef = React.createRef();
  }

  componentDidMount() {
    this.connect();
  }

  updateCounterValue() {
    this.counterValueRef.current.setValue(this.state.receivedCounterValue);
  }

  updateNumberOfConnectedUsers() {
    this.numberOfConnectedUsersRef.current.setValue(this.state.numberOfConnectedUsers);
  }

  connect() {
    var socket = new WebSocket('ws://localhost:6789/');
    socket.onopen = function () {
      console.log('Connected!');
    };

    socket.onmessage = (event) => {
      console.log('Received data: ' + event.data);

      var data = JSON.parse(event.data);

      switch (data.type) {
        case 'state':
          this.setState({ receivedCounterValue: data.value }, this.updateCounterValue);
          break;
        case 'users':
          this.setState({ numberOfConnectedUsers: data.count }, this.updateNumberOfConnectedUsers);
          break;
        default:
          console.error("unsupported event", data);
      }

      console.log('receivedCounterValue: ', this.state.receivedCounterValue)
      console.log('numberOfConnectedUsers: ', this.state.numberOfConnectedUsers)
    };

    socket.onclose = function () {
      console.log('Lost connection!');
    };

    socket.onerror = function () {
      console.log('Error!');
    };

    this.setState({ websocket: socket });
  }

  decrementCount() {
    console.log('decrementing count');
    this.state.websocket.send(JSON.stringify({ action: 'minus' }));
  }

  incrementCount() {
    console.log('incrementing count');
    this.state.websocket.send(JSON.stringify({ action: 'plus' }));
  }

  render() {
    return (
      <React.Fragment>
        <div>
          <header>
            <title> Counting stuff with websockets </title>
          </header>
        </div>

        <div className='buttons'>
          <button className='minus button' onClick={() => this.decrementCount()} > - </button>
          <button className='value  button' onClick={() => this.incrementCount()}> + </button>
        </div>

        <div>
          <SimpleContent ref={this.counterValueRef} header='Counter Value: ' value={this.state.receivedCounterValue} > </SimpleContent>
        </div>

        <div className='connected'>
          <SimpleContent ref={this.numberOfConnectedUsersRef} header='# of connected users: ' value={this.state.numberOfConnectedUsers} > </SimpleContent>
        </div>

      </React.Fragment>

    );
  }
}

export default App;

