const express = require("express");
const router = express.Router();
const bcrypt = require("bcryptjs");
const jwt = require("jsonwebtoken");
const User = require("../models/User");
const Patient = require("../models/Patient");
const Doctor = require("../models/Doctor");

router.post("/login", async (req, res) => {
  const { username, password } = req.body;
  try {
    const user = await User.findOne({ username });
    if (!user) {
      return res.status(400).json({ message: "Invalid credentials" });
    }
    const isMatch = await bcrypt.compare(password, user.password);
    if (!isMatch) {
      return res.status(400).json({ message: "Invalid credentials" });
    }
    const payload = { user: { id: user._id, role: user.role } };
    jwt.sign(
      payload,
      process.env.JWT_SECRET,
      { expiresIn: "1h" },
      (err, token) => {
        if (err) throw err;
        res.json({ token, role: user.role });
      }
    );
  } catch (err) {
    res.status(500).json({ message: err.message });
  }
});

router.post("/register", async (req, res) => {
  const { username, password, role, name, contact } = req.body;
  try {
    let user = await User.findOne({ username });
    if (user) {
      return res.status(400).json({ message: "User already exists" });
    }
    user = new User({
      username,
      password: await bcrypt.hash(password, 10),
      role,
    });
    await user.save();

    if (role === "patient") {
      const patient = new Patient({ userId: user._id, name, contact });
      await patient.save();
      user.userId = patient._id;
    } else if (role === "doctor") {
      const doctor = new Doctor({ userId: user._id, name, specialty: contact });
      await doctor.save();
      user.userId = doctor._id;
    }
    await user.save();

    res.json({ message: "User registered" });
  } catch (err) {
    res.status(500).json({ message: err.message });
  }
});

module.exports = router;
